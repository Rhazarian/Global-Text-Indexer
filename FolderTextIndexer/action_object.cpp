#include "action_object.h"

namespace {

	struct cancellation_exception : std::exception {
	};

}

action_object::action_object()
{
	qRegisterMetaType<std::exception_ptr>("std::exception_ptr");
}

action_object::~action_object() = default;

void action_object::request_cancellation()
{
	is_cancel_req = true;
}

bool action_object::is_cancellation_requested() const
{
	return is_cancel_req;
}

void action_object::cancellation_point() const
{
	if (is_cancellation_requested())
	{
		throw cancellation_exception();
	}
}

void action_object::handle_catch()
{
	ex_ptr = std::current_exception();
}

void action_object::handle_finish()
{
	if (!ex_ptr || is_cancellation_requested())
	{
		emit finished(is_cancellation_requested());
		return;
	}
	emit exception_is_thrown(ex_ptr);
}