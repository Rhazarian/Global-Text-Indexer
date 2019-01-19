#pragma once

#include <QDialog>
#include "ui_add_directory_dialog.h"

#include <string>
#include <optional>

struct add_directory_dialog : public QDialog
{
	Q_OBJECT

public:
	add_directory_dialog(QWidget *parent = Q_NULLPTR);
	~add_directory_dialog();

	std::optional<std::string> get_dir();

private:
	void validate_dir();
	void choose_dir();
	void reset();

	Ui::add_directory_dialog ui;
};