#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H

#include <QWidget>

class ChartWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
public slots:
    void updatePixmap(const QPixmap &pix);
signals:

private:
    QPixmap m_pix;
};

#endif // SCOREWIDGET_H
