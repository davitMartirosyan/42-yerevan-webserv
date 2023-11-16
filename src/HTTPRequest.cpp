/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:14:54 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/16 23:23:23 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest( void )
{
    reqLineEnd = 0;
    bodyEnd = 0;
    bodySize = 0;
    functionMap["GET"] = &HTTPRequest::get;
    functionMap["POST"] = &HTTPRequest::post;
    functionMap["DELETE"] = &HTTPRequest::delet;
}

HTTPRequest::~HTTPRequest()
{
}


std::string const &HTTPRequest::requestMethod( void ) const
{
    return (method);
}

std::string const &HTTPRequest::requestPath( void ) const
{
    return (path);
}

std::string const &HTTPRequest::requestVersion( void ) const
{
    return (version);
}

std::string HTTPRequest::rtrim(const std::string &str)
{
    size_t end = str.find_last_not_of(" \n\t\f\v");
    return (end == std::string::npos ? str : str.substr(0, end + 1));
}

std::string HTTPRequest::ltrim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \n\t\f\v");
    return (start == std::string::npos ? str : str.substr(start));
}

std::string HTTPRequest::trim(const std::string &str)
{
    return (ltrim(rtrim(str)));
}

void HTTPRequest::parsing(sock_t fd)
{
    int isValid = 0;
    if ((reqLineEnd = httpRequest.find_first_of("\r\n")) != std::string::npos)
    {
        request = httpRequest.substr(0, reqLineEnd+2);
        method = request.substr(0, request.find(" "));
        request.erase(0, method.size()+1);
        path = request.substr(0, request.find(" "));
        request.erase(0, path.size()+1);
        version = request.substr(0, request.find("\r\n"));
        // httpRequest.erase(0, method.size()+path.size()+version.size()+4);
        httpRequest.erase(0, reqLineEnd+2);
    }
    if ((bodyEnd = httpRequest.find("\r\n\r\n")) != std::string::npos)
    {
        headers = httpRequest.substr(0, bodyEnd);
        // HTTPRequest::charChange(headers, '\r', '*');
        // HTTPRequest::charChange(headers, '\n', '-');
        // std::cout << "+++++++++++++" << std::endl;
        // std::cout << headers << std::endl;
        // std::cout << "+++++++++++++" << std::endl;
        std::string httpHeaderLine;
        std::stringstream keyValuePairs(trim(headers));
        while (std::getline(keyValuePairs, httpHeaderLine, '\n'))
        {
            size_t pair = 0;
            if ((pair = httpHeaderLine.find_first_of(":")) != std::string::npos)
            {
                if (std::isspace(httpHeaderLine[pair+1]))
                {
                    std::string key = trim(httpHeaderLine.substr(0, pair));
                    std::string value = trim(httpHeaderLine.substr(pair+1, httpHeaderLine.find("\r")));
                    // std::cout << key << "=" << value << std::endl;
                    this->httpHeaders.insert(std::make_pair(key, value));
                    key.clear();
                    value.clear();
                    httpHeaderLine.clear();
                }
                else
                    isValid = -3;
            }
            else
                isValid = -2;
        }
    }
    else
        isValid = -1;
}

void HTTPRequest::processing(sock_t fd)
{
    std::map<std::string, void(HTTPRequest::*)( void )>::iterator function = functionMap.find(method);
    if (function != functionMap.end())
       ( this->*(function->second))();
}

void HTTPRequest::charChange(std::string &str, char s, char d)
{
    for(size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == s)
            str[i] = d;
    }
}

std::string HTTPRequest::findInMap(std::string key)
{
    std::map<std::string, std::string>::iterator in = httpHeaders.find(key);
    if (in != httpHeaders.end())
        return (in->second);
    std::string nill;
    return (nill);
}

void HTTPRequest::get( void )
{
    std::cout << "method is GET" << std::endl;
}
void HTTPRequest::post( void )
{
    std::cout << "method is POST" << std::endl;
    std::cout << findInMap("Content-Length") << std::endl;
}
void HTTPRequest::delet( void )
{
    std::cout << "method is DELETE" << std::endl;
}