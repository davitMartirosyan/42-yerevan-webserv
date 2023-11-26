/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:14:28 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/26 02:04:54 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQ_HPP
#define REQ_HPP
#include "Libs.hpp"
#include "HTTPResponse.hpp"

class Location;
class HTTPServer;
class HTTPRequest : public HTTPResponse
{
	public:
		HTTPRequest( void );
		~HTTPRequest();
    public:
        std::string findInMap(std::string key);
        void showHeaders( void );
    public:
        static bool isDir(std::string const &filePath);
        static bool isFile(std::string const &filePath);
        static bool isExist(std::string const &filePath);
    protected:
        void checkPath(HTTPServer const &srv);
        int in(std::string const &method);
        void processing(HTTPServer &srv);
        void processing(sock_t fd);
        static void charChange(std::string &str, char s, char d);
        static void lastChar(std::string &str, char s);
        static void firstChar(std::string &str, char s);
        std::string const &requestMethod( void ) const;
        std::string const &requestPath( void ) const;
        std::string const &requestVersion( void ) const;
        std::string ltrim(const std::string &str);
        std::string rtrim(const std::string &str);
        std::string trim(const std::string &str);
    protected:
        size_t reqLineEnd;
        size_t bodyEnd;
		char *http;
        std::string httpRequest;
        std::string request;
        std::string method;
        std::string path;
        std::string realPath;
        std::string actualPath;
        std::string extension;
        std::string queryString;
        std::string version;
        std::string headers;
        std::string body;
    protected:
        std::map<std::string, std::string> httpHeaders;
    protected:
        std::string boundary;
        std::string boundaryEnd;
        std::string contentType;
        std::string transferEncoding;
        std::string type;
        unsigned long int bodySize;
    protected:
        std::vector<std::string> methods;
        std::map<std::string, void (HTTPRequest::*)(HTTPServer&)> methodsMap;
        std::map<std::string, void (HTTPRequest::*)(sock_t)> contentMap;
    protected:
        void get(HTTPServer &srv);
        void post(HTTPServer &srv);
        void delet(HTTPServer &srv);


    protected:
        std::string dir_content(std::string const &realPath);
    public:
        std::string const &getResponse( void );
    protected:
        std::string response;
};



#endif