/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:14:54 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/19 01:57:04 by dmartiro         ###   ########.fr       */
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
    //boundary = "&"; // !IMPORTANT: if GET request: the boundary is (&) else if POST request: boundary is read from (Headers)
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
    size_t end = str.find_last_not_of(" \r\n\t\f\v");
    return (end == std::string::npos ? "" : str.substr(0, end + 1));
}

std::string HTTPRequest::ltrim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \r\n\t\f\v");
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
        httpRequest.erase(0, reqLineEnd+2);
    }
    if ((bodyEnd = httpRequest.find("\r\n\r\n")) != std::string::npos)
    {
        headers = httpRequest.substr(0, bodyEnd);
        httpRequest.erase(0, bodyEnd+4);
        std::string httpHeaderLine;
        std::stringstream keyValuePairs(headers);
        while (std::getline(keyValuePairs, httpHeaderLine, '\n'))
        {
            size_t pair = 0;
            if ((pair = httpHeaderLine.find_first_of(":")) != std::string::npos)
            {
                if (std::isspace(httpHeaderLine[pair+1]))
                {
                    std::string key = trim(httpHeaderLine.substr(0, pair));
                    std::string value = trim(httpHeaderLine.substr(pair+1, httpHeaderLine.find("\r")));
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
    std::map<std::string, void(HTTPRequest::*)(sock_t)>::iterator function = functionMap.find(method);
    if (function != functionMap.end())
       ( this->*(function->second))(fd);
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

void HTTPRequest::get(sock_t fd)
{
    // std::cout << "method is GET" << std::endl;
}
void HTTPRequest::post(sock_t fd)
{
    // std::cout << "method is POST" << std::endl;
    std::string contentType = findInMap("Content-Type");
    if (!contentType.empty())
    {
        std::string contentLength = findInMap("Content-Length");
        const char *offset = "boundary=";
        size_t boundaryPos = 0;
        if ((boundaryPos = contentType.find(offset)) != std::string::npos)
        {
            boundary = "--" + contentType.substr(boundaryPos+std::strlen(offset));
            boundaryEnd = (!boundary.empty() && boundary != "--") ? boundary + "--" : "";
        }
        if (!contentLength.empty())
            bodySize = std::atoi(contentLength.c_str());
    }
    else
        std::cout << "Not found" << std::endl;
}

void HTTPRequest::delet(sock_t fd)
{
    // std::cout << "method is DELETE" << std::endl;
}