/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:34:43 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/30 14:03:17 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpRequest.hpp"

HttpRequest::HttpRequest(std::string const &request) : requestLine(), header()
{
    std::cout << request << std::endl;
    req = request;
    parseHttpRequest(req);
}

HttpRequest::~HttpRequest()
{
}

std::string const &HttpRequest::method( void ) const
{
    return (this->requestLine[0]);
}

std::string const &HttpRequest::url( void ) const
{
    return (this->requestLine[1]);
}

std::string const &HttpRequest::httpVersion( void ) const
{
    return (this->requestLine[2]);
}

std::string const &HttpRequest::getBody( void ) const
{
    return (this->body);
}

void HttpRequest::parseHttpRequest(std::string &req)
{
    getRequestLine(req);
    getHeader(req);
    if (req.size() > 2)
        getBody(req);
}
void HttpRequest::getRequestLine(std::string &req)
{   
    size_t firstPoint = req.find_first_of("\r\n");
    if ( firstPoint != std::string::npos)
    {
        std::string reqLine = req.substr(0, firstPoint);
        req = req.substr(firstPoint+2);
        std::string token;
        for(size_t i = 0; i <= reqLine.size(); i++)
        {
            if (reqLine[i] == ' ' || reqLine[i] == '\0')
            {
                requestLine.push_back(token); 
                token.erase();
            }
            else
                token += reqLine[i];
        }
    }
    else
    {
        std::cerr << "Error: Malformed HTTP request. Could not find \\r\\n characters." << std::endl;
        return ;
    }
}

void HttpRequest::getHeader(std::string &req)
{
    std::string line;
    std::stringstream iostream(req);
    while(std::getline(iostream, line))
    {
        size_t semi = line.find(":");
        if (semi != std::string::npos)
        {
            std::string key = line.substr(0, semi);
            std::string value = line.substr(semi + 1);
            header.insert(std::make_pair(trim(key), trim(value)));
            req.erase(0, key.size()+value.size()+2);
        }
    }
}

void HttpRequest::getBody(std::string &req)
{
    req.erase(0, 2);
    body = req;
}

std::string HttpRequest::rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(" \n\t\f\v\r");
    return (end == std::string::npos ? "" : s.substr(0, end + 1));
}

std::string HttpRequest::ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(" \n\t\f\v\r");
    return (start == std::string::npos ? s : s.substr(start));
}

std::string HttpRequest::trim(const std::string &s)
{
    return (ltrim(rtrim(s)));
}