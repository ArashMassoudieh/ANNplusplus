#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#endif // ERRORHANDLER_H

#include <vector>
#include <string>
using namespace std;

struct _error
{
    string func;
    int errorcode;
    string error_description;
};



class ErrorHandler
{
public:
    ErrorHandler();
    void AppendError (const string &func, const int &errcode, const string &description);
    string toString(int i);
    int RecentErrorsNumber();

private:
    vector<_error> errors;
    int written_up_to;
};
