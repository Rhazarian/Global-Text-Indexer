#pragma once

#include <QDialog>
#include "ui_details_dialog.h"

class details_dialog : public QDialog
{
	Q_OBJECT

public:
	details_dialog(std::string path, std::tuple<QVector<std::tuple<size_t, size_t, std::string>>, size_t> data, QWidget *parent = Q_NULLPTR);
	~details_dialog();

private:
	Ui::details_dialog ui;

	std::string path;
private slots:
	void open_file();
};
