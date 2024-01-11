#include "performance.h"
#include "ui_performance.h"

Performance::Performance(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::Performance)
{
    double  numOfProcessors = 0;
    double  memTotalPhys = 0;

    ui->setupUi(this);

    m_sSettingsFile = INI_FILE;

    m_FileStorage = _settings.loadStringSetting(m_sSettingsFile, "General", "FileStorage");

#ifdef _WIN32

    QString value;

    PDH_STATUS status;

    status = PdhOpenQuery(nullptr, 0, &m_query);
    qDebug() << "PdhOpenQuery" << status;

    value = _settings.loadStringSetting(m_sSettingsFile, "Performance", "Cpu");
    if (value.isEmpty()) {
        status = PdhAddEnglishCounter(m_query, L"\\Processor(_Total)\\% Processor Time", 0, &m_cpuTotal);
    } else {
        status = PdhAddEnglishCounter(m_query, reinterpret_cast<LPCWSTR>(value.constData()), 0, &m_cpuTotal);
        qDebug() << "PdhAddCounter" << status << value ;
    }

    value = _settings.loadStringSetting(m_sSettingsFile, "Performance", "Memory");
    if (value.isEmpty()) {
        status = PdhAddEnglishCounter(m_query, L"\\Memory\\Available MBytes", 0, &m_memFree);
    } else {
        status = PdhAddEnglishCounter(m_query, reinterpret_cast<LPCWSTR>(value.constData()), 0, &m_memFree);
        qDebug() << "PdhAddCounter" << status << value;
    }

    /*
    value = _settings.loadStringSetting(m_sSettingsFile, "Performance", "Discspace");
    if (value.isEmpty()) {
        status = PdhAddEnglishCounter(m_query, L"\\LogicalDisk(T:)\\% Free Space", 0, &m_storageFree);
    } else {
        status = PdhAddEnglishCounter(m_query, reinterpret_cast<LPCWSTR>(value.constData()), 0, &m_storageFree);
        qDebug() << "PdhAddCounter" << status << value;
    }
    */

    status = PdhCollectQueryData (m_query);
    qDebug() << "PdhCollectQueryData" << status ;

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    numOfProcessors = sysInfo.dwNumberOfProcessors;

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    memTotalPhys = memInfo.ullTotalPhys;
#endif

#ifdef linux

    FILE* fd = fopen("/proc/stat", "r");
    int ret = fscanf(fd, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow, &lastTotalSys, &lastTotalIdle);
    fclose(fd);

    numOfProcessors = sysconf(_SC_NPROCESSORS_ONLN);

    sysinfo(&memInfo);
    memTotalPhys = ((uint64_t) memInfo.totalram * memInfo.mem_unit)/1024;

#endif

    QStorageInfo storage;
    storage.setPath( m_FileStorage ) ;

    cpuLayout = new QHBoxLayout( this );
    cpuLayout->setMargin( 15 );
    cpuLayout->setSpacing( 5 );

    ValueBarCpu = new ValueBar( Qt::Horizontal, "CPU: (" + QString("%1").arg(numOfProcessors) + " Cores)", this, 100 );
    ValueBarCpu->setFontSize(6);

    ValueBarMemory = new ValueBar( Qt::Horizontal, "RAM: (" + QString("%1").arg((uint64_t)(memTotalPhys / ( 1024 * 1024 )) ) + " MB)", this, (uint64_t)(memTotalPhys / ( 1024 * 1024 ) ) ) ;
    ValueBarMemory->setFontSize(6);

    ValueBarStorage = new ValueBar( Qt::Horizontal, "Storage: (" + QString(" %1 - %2/%3 GB free/total)").arg(m_FileStorage).arg(storage.bytesAvailable() / 1024 / 1024 / 1024 ).arg(storage.bytesTotal() / 1024 / 1024 /1024), this, storage.bytesTotal() / 1024 / 1024 /1024 );
    ValueBarStorage->setFontSize(6);

    cpuLayout->addWidget( ValueBarCpu );
    cpuLayout->addWidget( ValueBarMemory );
    cpuLayout->addWidget( ValueBarStorage );

    // create a timer
    timer = new QTimer(this);

    // setup signal and slot
    connect(timer, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));

    // msec
    timer->start(1000);
}

Performance::~Performance()
{
    delete ui;
}

void Performance::MyTimerSlot()
{
#ifdef _WIN32

    PDH_FMT_COUNTERVALUE counterVal;

    PdhCollectQueryData(m_query);

    PdhGetFormattedCounterValue(m_cpuTotal, PDH_FMT_DOUBLE, nullptr, &counterVal);
    ValueBarCpu->setValue( counterVal.doubleValue );

    PdhGetFormattedCounterValue(m_memFree, PDH_FMT_DOUBLE, nullptr, &counterVal);   
    ValueBarMemory->setValue( counterVal.doubleValue );

#endif

#ifdef linux

     double percent;
     FILE* file;

     unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

     file = fopen("/proc/stat", "r");
     int ret = fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow, &totalSys, &totalIdle);
     fclose(file);

     if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow || totalSys < lastTotalSys || totalIdle < lastTotalIdle){
         //Overflow detection. Just skip this value.
         percent = -1.0;
     }
     else{
         total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
             (totalSys - lastTotalSys);
         percent = total;
         total += (totalIdle - lastTotalIdle);
         percent /= total;
         percent *= 100;
     }

     lastTotalUser = totalUser;
     lastTotalUserLow = totalUserLow;
     lastTotalSys = totalSys;
     lastTotalIdle = totalIdle;

     ValueBarCpu->setValue( percent );

     /* Memory */

     sysinfo(&memInfo);
     m_memFree = ((uint64_t) memInfo.freeram * memInfo.mem_unit ) / 1024;
     ValueBarMemory->setValue( (uint64_t) m_memFree / 1024 );

#endif

     /* Diskspace */

     QStorageInfo storage;
     storage.setPath( m_FileStorage ) ;
     ValueBarStorage->setValue( storage.bytesAvailable() / 1024 / 1024 / 1024 );
}
