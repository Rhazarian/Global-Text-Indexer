#pragma once

#include <atomic>
#include <stdexcept>

#include <QObject>
#include <QMetaType>

Q_DECLARE_METATYPE(std::exception_ptr);

struct action_object : public QObject
{
	Q_OBJECT

public:
	action_object();
	virtual ~action_object();
	action_object& operator=(action_object const&) = delete;
	action_object(action_object const&) = delete;

	void request_cancellation();
	bool is_cancellation_requested() const;

public slots:
	virtual void process() = 0;

protected:
	void cancellation_point() const;
	void handle_catch();
	void handle_finish();

signals:
	void exception_is_thrown(std::exception_ptr ex_ptr);
	void set_progress_max(int progress);
	void set_progress(int progress);
	void finished(bool cancelled);

private:
	std::atomic_bool is_cancel_req{ false };
	std::exception_ptr ex_ptr{ nullptr };
};