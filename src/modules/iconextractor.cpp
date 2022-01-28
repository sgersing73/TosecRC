#include "iconextractor.h"


iconExtractor::iconExtractor()
{

}

#ifdef WIN32
QString iconExtractor::formatSizeText(const QSize &size)
{
    return QString::number(size.width()) + QLatin1Char('x') + QString::number(size.height());
}

// Extract icons contained in executable or DLL using the Win32 API ExtractIconEx()
PixmapEntryList iconExtractor::extractIcons(const QString &sourceFile, bool large)
{
    const QString nativeName = QDir::toNativeSeparators(sourceFile);
    const wchar_t *sourceFileC = reinterpret_cast<const wchar_t *>(nativeName.utf16());
    const UINT iconCount = ExtractIconEx(sourceFileC, -1, nullptr, nullptr, 0);
    if (!iconCount) {
        qDebug() << sourceFile << " does not appear to contain icons.\n";
        return PixmapEntryList();
    }

    QScopedArrayPointer<HICON> icons(new HICON[iconCount]);
    const UINT extractedIconCount = large ?
        ExtractIconEx(sourceFileC, 0, icons.data(), nullptr, iconCount) :
        ExtractIconEx(sourceFileC, 0, nullptr, icons.data(), iconCount);
    if (!extractedIconCount) {
        qErrnoWarning("Failed to extract icons from %s", qPrintable(sourceFile));
        return PixmapEntryList();
    }

    PixmapEntryList result;
    result.reserve(int(extractedIconCount));

    qDebug() << sourceFile << " contains " << extractedIconCount << " icon(s).\n";

    for (UINT i = 0; i < extractedIconCount; ++i) {
        PixmapEntry entry;
        entry.pixmap = QtWin::fromHICON(icons[i]);
        if (entry.pixmap.isNull()) {
            qDebug() << "Error converting icons.\n";
            return PixmapEntryList();
        }
        entry.name = QString::fromLatin1("%1_%2_%3x%4").arg(QFileInfo(sourceFile).baseName()).arg(i, 3, 10, QLatin1Char('0'))
            .arg(entry.pixmap.width()).arg(entry.pixmap.height());
        result.append(entry);
    }
    return result;
}

// Helper for extracting large/jumbo icons available from Windows Vista onwards
// via SHGetImageList().
QPixmap iconExtractor::pixmapFromShellImageList(int iImageList, const SHFILEINFO &info)
{
    QPixmap result;
    // For MinGW:
    static const IID iID_IImageList = {0x46eb5926, 0x582e, 0x4017, {0x9f, 0xdf, 0xe8, 0x99, 0x8d, 0xaa, 0x9, 0x50}};

    IImageList *imageList = nullptr;
    if (FAILED(SHGetImageList(iImageList, iID_IImageList, reinterpret_cast<void **>(&imageList))))
        return result;

    HICON hIcon = nullptr;
    if (SUCCEEDED(imageList->GetIcon(info.iIcon, ILD_TRANSPARENT, &hIcon))) {
        result = QtWin::fromHICON(hIcon);
        DestroyIcon(hIcon);
    }
    return result;
}


// Extract icons that would be  displayed by the Explorer (shell)
PixmapEntryList iconExtractor::extractShellIcons(const QString &sourceFile, bool addOverlays)
{
    enum { // Shell image list ids
        sHIL_EXTRALARGE = 0x2, // 48x48 or user-defined
        sHIL_JUMBO = 0x4 // 256x256 (Vista or later)
    };

    struct FlagEntry {
        const char *name;
        unsigned flags;
    };

    const FlagEntry modeEntries[] =
    {
        {"",     0},
        {"open", SHGFI_OPENICON},
        {"sel",  SHGFI_SELECTED},
    };
    const FlagEntry standardSizeEntries[] =
    {
        {"s",  SHGFI_SMALLICON},
        {"l",  SHGFI_LARGEICON},
        {"sh", SHGFI_SHELLICONSIZE},
    };

    const QString nativeName = QDir::toNativeSeparators(sourceFile);
    const wchar_t *sourceFileC = reinterpret_cast<const wchar_t *>(nativeName.utf16());

    SHFILEINFO info;
    unsigned int baseFlags = SHGFI_ICON | SHGFI_SYSICONINDEX | SHGFI_ICONLOCATION;
    if (addOverlays)
        baseFlags |= SHGFI_ADDOVERLAYS | SHGFI_OVERLAYINDEX;
    if (!QFileInfo(sourceFile).isDir())
        baseFlags |= SHGFI_USEFILEATTRIBUTES;

    PixmapEntryList result;
    for (auto modeEntry : modeEntries) {
        const unsigned modeFlags = baseFlags | modeEntry.flags;
        QString modePrefix = QLatin1String("_shell_");
        if (modeEntry.name[0])
            modePrefix += QLatin1String(modeEntry.name) + QLatin1Char('_');
        for (auto standardSizeEntry : standardSizeEntries) {
            const unsigned flags = modeFlags | standardSizeEntry.flags;
            const QString prefix = modePrefix + QLatin1String(standardSizeEntry.name)
                + QLatin1Char('_');
            ZeroMemory(&info, sizeof(SHFILEINFO));
            const HRESULT hr = SHGetFileInfo(sourceFileC, 0, &info, sizeof(SHFILEINFO), flags);
            if (FAILED(hr)) {
                _com_error error(hr);
                qDebug() << "SHGetFileInfo() failed for \"" << nativeName << "\", "
                    << std::hex << std::showbase << flags << std::dec << std::noshowbase
                    << " (" << prefix << "): " << error.ErrorMessage() << '\n';
                continue;
            }

            if (info.hIcon) {
                PixmapEntry entry;
                entry.pixmap = QtWin::fromHICON(info.hIcon);
                DestroyIcon(info.hIcon);
                if (entry.pixmap.isNull()) {
                    qDebug() << "Error converting icons.\n";
                    return PixmapEntryList();
                }
                entry.name = prefix + formatSizeText(entry.pixmap.size());

                const int iconIndex = info.iIcon & 0xFFFFFF;
                const int overlayIconIndex = info.iIcon >> 24;

                qDebug() << "Obtained icon #" << iconIndex;
                if (addOverlays)
                    qDebug() << " (overlay #" << overlayIconIndex << ')';
                if (info.szDisplayName[0])
                    qDebug() << " from " << QString::fromWCharArray(info.szDisplayName);
                qDebug() << " (" << entry.pixmap.width() << 'x'
                    << entry.pixmap.height() << ") for " << std::hex << std::showbase << flags
                    << std::dec << std::noshowbase << '\n';

                result.append(entry);
            }
        } // for standardSizeEntryCount
        // Windows Vista onwards: extract large/jumbo icons
        if (info.hIcon) {
            QPixmap extraLarge = this->pixmapFromShellImageList(sHIL_EXTRALARGE, info);
            if (!extraLarge.isNull()) {
                PixmapEntry entry;
                entry.pixmap = extraLarge;
                entry.name = modePrefix + QLatin1String("xl_") + formatSizeText(extraLarge.size());
                result.append(entry);
            }
            QPixmap jumbo = this->pixmapFromShellImageList(sHIL_JUMBO, info);
            if (!jumbo.isNull()) {
                PixmapEntry entry;
                entry.pixmap = jumbo;
                entry.name = modePrefix + QLatin1String("jumbo_") + formatSizeText(extraLarge.size());
                result.append(entry);
            }
        }
    } // for modes
    return result;
}
#endif
