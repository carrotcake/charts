#pragma once

#include <QGraphicsView>
#include <QWidget>

class ChartWidget : public QGraphicsView {
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = nullptr);
    // void paintEvent(QPaintEvent *) override;
public slots:
    void updatePixmap();
signals:

private:
};
