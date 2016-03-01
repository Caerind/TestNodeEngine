#ifndef ATLOG_HPP
#define ATLOG_HPP

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <functional>
#include <SFML/Network/Http.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class AtLog
{
    public:
        enum Type
        {
            None,
            Info,
            Warning,
            Error,
        };

	static AtLog& instance();

	friend AtLog& operator<<(AtLog& log, std::string message)
	{
	    std::ostringstream stream;
	    stream << "action=insert";

	    if(log.mType == Type::Info)
	        stream << "&type=info";
	    else if(log.mType == Type::Warning)
		stream << "&type=warning";
	    else if(log.mType == Type::Error)
		stream << "&type=error";
	    else
		stream << "&type=none";

	    if(log.mAppName != "")
		stream << "&appname=" << log.mAppName;

	    if(log.mAppVersion != "")
		stream << "&appversion=" << log.mAppVersion;

	    stream << "&address=" << sf::IpAddress::getPublicAddress().toString();

	    if(log.mUsername != "")
		stream << "&username=" << log.mUsername;

	    stream << "&content=" << message;

	    sf::Http::Request request("/Log/index.php", sf::Http::Request::Post);
        request.setBody(stream.str());
        sf::Http http("http://atmog.altervista.org");
        http.sendRequest(request,sf::seconds(10.f));

	    return log;
	}

	friend AtLog& operator<<(AtLog& log, Type type)
	{
	    log.mType = type;
	    return log;
	}

    void setAppName(std::string appName);
	void setAppVersion(std::string appVersion);
	void setUsername(std::string username);

    private:
        static AtLog* mInstance;

        Type mType;
        std::string mAppName;
        std::string mAppVersion;
        std::string mUsername;
};

#endif // ATLOG_HPP
