/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:14:54 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/21 21:27:28 by dmartiro         ###   ########.fr       */
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

void HTTPRequest::processing(sock_t fd)
{
    std::map<std::string, void(HTTPRequest::*)(sock_t)>::iterator function = functionMap.find(method);
    if (function != functionMap.end())
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
    contentType = findInMap("Content-Type");
    if (!contentType.empty())
    {
        // std::cout << "|"<<contentType<<"|" << std::endl;
        type = contentType.substr(0, contentType.find(";"));
        contentType.erase(0, contentType.find(";")+1);
        boundary = "--" + contentType.substr(contentType.find("=")+1);
        boundaryEnd = boundary + "--";
        // std::cout << "[" << type << "][" << boundary << "]" << std::endl;
    }
    
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
                content.push_back(line);
                line.erase();
            }
        }
        else
            line += get_next_line + "\r\n";
    }
    std::cout << httpRequest << std::endl;
}

void HTTPRequest::delet(sock_t fd)
{
    // std::cout << "method is DELETE" << std::endl;
}

void HTTPRequest::showHeaders( void )
{
    std::map<std::string, std::string>::iterator it;
    for(it = httpHeaders.begin(); it != httpHeaders.end(); it++)
    {
        std::cout << it->first << " = " << it->second << std::endl;
    }
}