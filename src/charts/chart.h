#ifndef CHART_H
#define CHART_H

#include <QObject>

class Chart : public QObject {
    Q_OBJECT
public:
    explicit Chart(QObject *parent = nullptr);

signals:
};

#endif // CHART_H
