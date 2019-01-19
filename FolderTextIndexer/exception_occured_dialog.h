#pragma once

#include <QDialog>
#include "ui_exception_occured_dialog.h"

struct exception_occured_dialog : public QDialog
{
	Q_OBJECT

public:
	exception_occured_dialog(std::string const& title, std::string const& message, QWidget *parent = Q_NULLPTR);
	~exception_occured_dialog();

private:
	Ui::exception_occured_dialog ui;
};
