#include "add_directory_dialog.h"

#include <QFileInfo>
#include <QFileDialog>

add_directory_dialog::add_directory_dialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.buttonBox->button(QDialogButtonBox::StandardButton::Cancel), &QPushButton::clicked, this, &QDialog::reject);
	connect(ui.buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::clicked, this, &QDialog::accept);
	connect(ui.lineEdit, &QLineEdit::textEdited, this, &add_directory_dialog::validate_dir);
	connect(ui.chooseDirectoryButton, &QPushButton::clicked, this, &add_directory_dialog::choose_dir);
}

add_directory_dialog::~add_directory_dialog() = default;

void add_directory_dialog::validate_dir()
{
	QFileInfo dir(ui.lineEdit->text());
	ui.buttonBox->button(QDialogButtonBox::StandardButton::Ok)->setEnabled(dir.exists() && dir.isDir());
}

void add_directory_dialog::choose_dir()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Directory"));
	if (!dir.isEmpty()) {
		ui.lineEdit->setText(dir);
	}
	validate_dir();
}

std::optional<std::string> add_directory_dialog::get_dir()
{
	reset();
	if (exec())
	{
		return { ui.lineEdit->text().toStdString() };
	}
	return {};
}

void add_directory_dialog::reset()
{
	ui.lineEdit->clear();
	ui.buttonBox->button(QDialogButtonBox::StandardButton::Ok)->setEnabled(false);
}