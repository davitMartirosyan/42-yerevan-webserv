/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:34:43 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/27 01:14:17 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lib.hpp"

HttpRequest::HttpRequest(std::string const &request) : requestLine(), header()
{
    std::cout << request;
    req = request;
    parseHttpRequest(req);
}

HttpRequest::~HttpRequest()
{
}

std::string const &HttpRequest::getMethod( void ) const
{
    return (this->requestMethod);
}

std::string const &HttpRequest::getUrl( void ) const
{
    return (this->requestUrl);
}

std::string const &HttpRequest::getHttpVersion( void ) const
{
    return (this->requestUrl);
}

void HttpRequest::parseHttpRequest(std::string &req)
{
    std::cout << "_______________________" << std::endl;
    getRequestLine(req);
    getHeaderPairs(req);
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

void HttpRequest::getHeaderPairs(std::string &req)
{
    size_t lineCount = 0;
    size_t i = -1;
    while (++i < req.size())
        if (req[i] == '\n')
            lineCount++;
    lineCount--;
}

std::string HttpRequest::rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(" \n\t\f\v");
    return (end == std::string::npos ? "" : s.substr(0, end + 1));
}

std::string HttpRequest::ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(" \n\t\f\v");
    return (start == std::string::npos ? s : s.substr(start));
}

std::string HttpRequest::trim(const std::string &s)
{
    return (ltrim(rtrim(s)));
}