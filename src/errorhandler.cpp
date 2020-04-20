#include "ErrorHandler.h"
#include "utils.h"

ErrorHandler::ErrorHandler()
{

}

void ErrorHandler::AppendError (const string &func, const int &errcode, const string &description)
{
    _error err;
    err.func = func;
    err.errorcode = errcode;
    err.error_description = description;
}

string ErrorHandler::toString(int i)
{
    if (i>errors.size()-1) return "none!";
    string s = errors[i].func + ":" + aquiutils::numbertostring(errors[i].errorcode) + ":" + errors[i].error_description;
    written_up_to = i;
    return s;
}

int ErrorHandler::RecentErrorsNumber()
{
    return errors.size()-written_up_to;
}
