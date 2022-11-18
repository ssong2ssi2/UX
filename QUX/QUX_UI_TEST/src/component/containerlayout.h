#pragma once

#include <QLayout>

class ContainerLayout : public QLayout
{
    Q_OBJECT

public:
    ContainerLayout(QWidget* parent = nullptr);
    ~ContainerLayout();

    void addLayout(QLayout* layout, Qt::Alignment alignment = 0);
    void addWidget(QWidget* widget, Qt::Alignment alignment = 0);

    void addItem(QLayoutItem *item) override;
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    int count() const override;
    QLayoutItem* itemAt(int) const override;
    QLayoutItem* takeAt(int) override;
    void setGeometry(const QRect &rect) override;

private:
    QList<QLayoutItem*> m_list;

};
