/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:14:54 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/15 00:52:48 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest( void )
{
    reqLineEnd = 0;
    bodyEnd = 0;
    bodySize = 0;
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

void HTTPRequest::parse(sock_t fd, char *httpBuffer)
{
    httpRequest.append(httpBuffer);
    if ((reqLineEnd = httpRequest.find_first_of("\r\n")) != std::string::npos)
    {
        int sp = 0;
        requestLine = httpRequest.substr(0, reqLineEnd);
        for(size_t i = 0; i < requestLine.size(); i++)
            if (requestLine[i] == ' ')
                sp++;
        if (sp == 2)
        {
            std::string tmpLine = requestLine;
            method = tmpLine.substr(0, tmpLine.find_first_of(" "));
            tmpLine.erase(0, tmpLine.find_first_of(" ") + 1);
            path = tmpLine.substr(0, tmpLine.find_first_of(" "));
            tmpLine.erase(0, tmpLine.find_first_of(" ") + 1);
            version = tmpLine;
            // httpRequest.erase(0, reqLineEnd + 2);
        }
    }
    if ((bodyEnd = httpRequest.find_last_of("\r\n")) != std::string::npos && reqLineEnd != std::string::npos)
    {
        body = httpRequest.substr(reqLineEnd, bodyEnd);
        std::stringstream bodyStream(body);
        std::string header;
        while(std::getline(bodyStream, header, '\n'))
        {
            size_t colon = 0;
            if ((colon = header.find_first_of(":")) != std::string::npos)
            {
                std::string key = trim(header.substr(0, colon));
                std::string value = trim(header.substr(colon+1));
                if (key.size() > 0 && value.size() > 0)
                {
                    httpHeaders.insert(std::make_pair(key, value));
                }
            }
        }
        // httpRequest.erase(0, bodyEnd + 2);
    }
    if (reqLineEnd != std::string::npos && bodyEnd != std::string::npos)
    {
        std::map<std::string, std::string>::iterator it = httpHeaders.begin();
        for(; it != httpHeaders.end(); it++)
        {
            if (it->first == "Content-Length")
                bodySize = strtoul(it->second.c_str(), NULL, 10);
            else if (it->first == "Content-Type")
                multipart = it->second;
        }
        unsigned long int test = 0;
        while (data.size() < bodySize)
        {
            char multipartData[2048];
            int r = recv(fd, multipartData, sizeof(multipartData), 0);
            multipartData[r] = '\0';
            data.append(multipartData);
        }
        std::fstream file;
        file.open("file.jpg", std::ios::out);
        file << data;
    }
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

const char *HTTPRequest::find(std::string const &key)
{
    std::map<std::string, std::string>::const_iterator it = httpHeaders.find(key);
    if (it != httpHeaders.end())
        return (it->second.c_str());
    return (NULL);
}