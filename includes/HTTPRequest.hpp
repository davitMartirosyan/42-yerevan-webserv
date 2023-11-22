/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:14:28 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/23 01:51:52 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQ_HPP
#define REQ_HPP
#include "Libs.hpp"

class HTTPRequest
{
	public:
		HTTPRequest( void );
		~HTTPRequest();
    public:
        std::string findInMap(std::string key);
        void showHeaders( void );
    public:
        void processing(sock_t fd);
        void contentReceiveMethod(sock_t fd);
        void prepareToTransfer(std::string const &content);
        static void charChange(std::string &str, char s, char d);
        std::string const &requestMethod( void ) const;
        std::string const &requestPath( void ) const;
        std::string const &requestVersion( void ) const;
        std::string ltrim(const std::string &str);
        std::string rtrim(const std::string &str);
        std::string trim(const std::string &str);
    protected:
        size_t reqLineEnd;
        size_t bodyEnd;
		char http[READ_BUFFER];
        std::string httpRequest;
        std::string request;
        std::string method;
        std::string path;
        std::string pathQuery;
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
        std::string cgiEnv;
    private:
        std::map<std::string, void (HTTPRequest::*)(sock_t)> methodsMap;
        std::map<std::string, void (HTTPRequest::*)(sock_t)> contentMap;
        void get(sock_t fd);
        void post(sock_t fd);
        void delet(sock_t fd);
    private:
        void multipart(sock_t fd);
        void wwwFormUrlEncoded(sock_t fd);
};



#endif