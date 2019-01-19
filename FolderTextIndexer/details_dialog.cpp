#include "details_dialog.h"

#include <QDesktopServices>
#include <QUrl>

details_dialog::details_dialog(std::string path, std::tuple<QVector<std::tuple<size_t, size_t, std::string>>, size_t> data, QWidget *parent) : QDialog(parent), path(std::move(path))
{
	ui.setupUi(this);
	ui.file_path_line_edit->setText(this->path.c_str());
	ui.file_path_line_edit->setReadOnly(true);
	ui.tree_widget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.tree_widget->setUniformRowHeights(true);
	const auto& vector = std::get<0>(data);
	for (const auto& [matches, line, text] : vector)
	{
		auto item = new QTreeWidgetItem();
		item->setText(0, QString::number(matches));
		item->setText(1, QString::number(line));
		item->setText(2, text.c_str());
		ui.tree_widget->addTopLevelItem(item);
	}
	connect(ui.open_file_button, &QPushButton::clicked, this, &details_dialog::open_file);
	connect(this, &details_dialog::finished, this, &details_dialog::deleteLater);
	open();
}

details_dialog::~details_dialog() = default;

void details_dialog::open_file()
{
	QDesktopServices::openUrl(QUrl::fromLocalFile(path.c_str()));
}