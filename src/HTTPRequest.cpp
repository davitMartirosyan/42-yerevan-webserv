/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:14:54 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/23 01:50:24 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest( void )
{
    reqLineEnd = 0;
    bodyEnd = 0;
    bodySize = 0;
    methodsMap["GET"] = &HTTPRequest::get;
    methodsMap["POST"] = &HTTPRequest::post;
    methodsMap["DELETE"] = &HTTPRequest::delet;
    //boundary = "&"; // !IMPORTANT: if GET request: the boundary is (&) else if POST request: boundary is read from (Headers)
    contentMap["multipart/form-data"] = &HTTPRequest::multipart;
    contentMap["application/x-www-form-urlencoded"] = &HTTPRequest::wwwFormUrlEncoded;
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

void HTTPRequest::processing(sock_t fd)
{
    std::map<std::string, void(HTTPRequest::*)(sock_t)>::iterator function = methodsMap.find(method);
    if (function != methodsMap.end())
       (this->*(function->second))(fd);
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
    if (!(contentType = findInMap("Content-Type")).empty())
    {
        type = trim(contentType.substr(0, contentType.find(";")));
        HTTPRequest::contentReceiveMethod(fd);
    }
    else if (!(transferEncoding = findInMap("Transfer-Encoding")).empty())
    {
        std::cout << "Data transfers chunck by chunk" << std::endl;
    }
}

void HTTPRequest::contentReceiveMethod(sock_t fd)
{
    std::map<std::string, void (HTTPRequest::*)(sock_t)>::iterator function = contentMap.find(type);
    if (function != contentMap.end())
        (this->*(function->second))(fd);
    else
        std::cout << "nothing" << std::endl;
}

void HTTPRequest::prepareToTransfer(std::string const &content)
{
    
}

void HTTPRequest::delet(sock_t fd)
{
    // std::cout << "method is DELETE" << std::endl;
}

void HTTPRequest::multipart(sock_t fd)
{
    std::cout << "multipart/form-data" << std::endl;
    std::cout << httpRequest << std::endl;
    contentType.erase(0, contentType.find(";")+1);
    boundary = "--" + contentType.substr(contentType.find("=")+1);
    boundaryEnd = boundary + "--";
    std::stringstream iss(httpRequest);
    std::vector<std::string> content;
    std::string line;
    std::string get_next_line;
    while (std::getline(iss, get_next_line))
    {
        if (trim(get_next_line) == boundary || trim(get_next_line) == boundaryEnd)
        {
            if (!line.empty())
            {
                HTTPRequest::prepareToTransfer(line);
                // content.push_back(line);
                line.erase();
            }
        }
        else
            line += get_next_line + "\r\n";
    }
}

void HTTPRequest::wwwFormUrlEncoded(sock_t fd)
{
    std::cout << "application/x-www-form-urlencoded" << std::endl;
}

void HTTPRequest::showHeaders( void )
{
    std::map<std::string, std::string>::iterator it;
    for(it = httpHeaders.begin(); it != httpHeaders.end(); it++)
    {
        std::cout << it->first << " = " << it->second << std::endl;
    }
}

