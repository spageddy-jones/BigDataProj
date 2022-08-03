#include "ui.h"

#include <iostream>
#include <vector>

#include "httplib.h"

static const char *hostname = "127.0.0.1";
static const int port = 8080;

static int routeCount = 0;
static bool initialized = false;

static httplib::Server svr;

static std::vector<std::string> commands;
static std::map<std::string, std::string> values; 

bool uiRegisterCommand(const std::string name, std::function<std::string(const std::string &)> fn)
{
    if (initialized)
    {
        std::cerr << "Tried to add a command after initialization: " << name << std::endl;
        return false;
    }

    if (std::find(commands.begin(), commands.end(), name) != commands.end())
    {
        std::cerr << "Tried to add a duplicate command: " << name << std::endl;
        return false;
    }

    svr.Post(std::string("/cmd/") + name, [fn](const httplib::Request &req, httplib::Response &res) {
        res.set_content(fn(req.body), "text/plain");
    });

    routeCount += 1;
    return true;
}

bool uiRegisterValue(const std::string &name)
{
    if (initialized)
    {
        std::cerr << "Tried to add a value after initialization: " << name << std::endl;
        return false;
    }

    if (values.find(name) != values.end())
    {
        std::cerr << "Tried to add a duplicate value: " << name << std::endl;
        return false;
    }

    values[name] = "";

    svr.Get(std::string("/value/") + name, [name](const httplib::Request &, httplib::Response &res) {
        res.set_content(values[name], "text/plain");
    });

    routeCount += 1;
    return true;
}

bool uiSetValue(const std::string &name, const std::string &value)
{
    if (values.find(name) == values.end())
    {
        std::cerr << "Unable to set unregistered value: " << name << std::endl;
        return false;
    }

    values[name] = value;
    return true;
}

static void uiInitialize()
{
    uiRegisterValue("ping");
    uiSetValue("ping", "pong");

    uiRegisterCommand("ping", [](const std::string &in) { return in; });

    std::cout << "Initialized " << routeCount << " UI API route(s)" << std::endl;
    initialized = true;
}

void uiListen()
{
    uiInitialize();

    std::cout << "UI API is listening on " << hostname << ":" << port << std::endl;
    svr.listen(hostname, port);
}
