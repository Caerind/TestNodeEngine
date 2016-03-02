#include "HttpThread.hpp"

namespace lp
{

HttpThread::HttpThread()
: mThread(std::bind(&HttpThread::run,this))
, mMessage("")
{
    mRunning = true;
    mThread.launch();
}

HttpThread::HttpThread(std::string const& url, std::string const& uri)
: mThread(std::bind(&HttpThread::run,this))
, mMessage("")
, mUrl(url)
, mUri(uri)
{
    mRunning = true;
    mThread.launch();
}

HttpThread::~HttpThread()
{
    mRunning = false;
    mThread.wait();
}

void HttpThread::run()
{
    while (mRunning)
    {
        if (mMessage != "")
        {

            sf::Http http(mUrl);
            sf::Http::Request request(mUri, sf::Http::Request::Post);
            request.setBody(mMessage);

            mMutex.lock();
            mMessage = "";
            mMutex.unlock();

            http.sendRequest(request);
        }
    }
}

void HttpThread::setAddress(std::string const& url, std::string const& uri)
{
    mMutex.lock();
    mUrl = url;
    mUri = uri;
    mMutex.unlock();
}

void HttpThread::setMessage(std::string const& message)
{
    mMutex.lock();
    mMessage = message;
    mMutex.unlock();
}

} // namespace lp
