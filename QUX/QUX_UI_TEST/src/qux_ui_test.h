#pragma once

#include <QWidget>
#include "ui_QUX_UI_TEST.h"

class QUX_UI_TEST : public QWidget
{
    Q_OBJECT

public:
    QUX_UI_TEST(QWidget *parent = nullptr);
    
public:
    void initFluxModel();
    void setupUI();

};
