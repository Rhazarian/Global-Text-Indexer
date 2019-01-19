#include "exception_occured_dialog.h"

exception_occured_dialog::exception_occured_dialog(std::string const& title, std::string const& message, QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);
	ui.title_label->setText(title.c_str());
	ui.message_text_browser->setText(message.c_str());
	connect(ui.ok_button, &QPushButton::clicked, this, &exception_occured_dialog::accept);
	connect(this, &exception_occured_dialog::accept, this, &exception_occured_dialog::deleteLater);
	open();
}

exception_occured_dialog::~exception_occured_dialog() = default;
