#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <QGroupBox>
#include <QDebug>
#include <QTimer>
#include <QStorageInfo>
#include <QLabel>
#include <QLayout>
#include <QStorageInfo>

#include "config.h"
#include "src/modules/settings.h"
#include "src/modules/valuebar.h"

#ifdef _WIN32
#include "pdh.h"
#endif

#ifdef linux
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "unistd.h"
#endif

namespace Ui {
class Performance;
}

class Performance : public QGroupBox
{
    Q_OBJECT

public:
    explicit Performance(QWidget *parent = nullptr);
    ~Performance();

public slots:
    void MyTimerSlot();

private:
    Ui::Performance *ui;
    QHBoxLayout     *cpuLayout;

    ValueBar        *ValueBarCpu;
    ValueBar        *ValueBarMemory;
    ValueBar        *ValueBarStorage;

    QTimer          *timer;

#ifdef _WIN32
    PDH_HQUERY      m_query;
    PDH_HCOUNTER    m_cpuTotal;
    PDH_HCOUNTER    m_memFree;
    PDH_HCOUNTER    m_storageFree;
#else
    int             m_query;
    int             m_cpuTotal;
    int             m_memFree;
    int             m_storageFree;

    struct sysinfo  memInfo;
#endif

    QString         m_FileStorage;
    QString         m_sSettingsFile;

    settings        _settings;

    unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
    unsigned long long totalPhysMem;
};

#endif // PERFORMANCE_H
