/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMetaProvider.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:37:48 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/30 14:28:46 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HttpMetaProvider.hpp"

HttpMetaProvider::HttpMetaProvider( void )
{
    Mimes();
    Methods();
}

HttpMetaProvider::~HttpMetaProvider()
{
}

void HttpMetaProvider::Mimes( void )
{
    types.insert(std::make_pair( ".txt", "text/plain"));
    types.insert(std::make_pair(".php", "text/html"));
    types.insert(std::make_pair( ".html", "text/html"));
    types.insert(std::make_pair( ".htm", "text/html"));
    types.insert(std::make_pair( ".css", "text/css"));
    types.insert(std::make_pair( ".js", "text/javascript"));
    types.insert(std::make_pair( ".xml", "text/xml"));
    types.insert(std::make_pair( ".csv", "text/csv"));
    types.insert(std::make_pair( ".jpg", "image/jpeg"));
    types.insert(std::make_pair( ".jpeg", "image/jpeg"));
    types.insert(std::make_pair( ".png", "image/png"));
    types.insert(std::make_pair( ".gif", "image/gif"));
    types.insert(std::make_pair( ".bmp", "image/bmp"));
    types.insert(std::make_pair( ".svg", "image/svg+xml"));
    types.insert(std::make_pair( ".webp", "image/webp"));
    types.insert(std::make_pair( ".mp3", "audio/mpeg"));
    types.insert(std::make_pair( ".wav", "audio/wav"));
    types.insert(std::make_pair( ".ogg", "audio/ogg"));
    types.insert(std::make_pair( ".aac", "audio/aac"));
    types.insert(std::make_pair( ".flac", "audio/flac"));
    types.insert(std::make_pair( ".mp4", "video/mp4"));
    types.insert(std::make_pair( ".webm", "video/webm"));
    types.insert(std::make_pair( ".ogv", "video/ogg"));
    types.insert(std::make_pair( ".mpeg", "video/mpeg"));
    types.insert(std::make_pair( ".mpg", "video/mpeg"));
    types.insert(std::make_pair( ".avi", "video/avi"));
    types.insert(std::make_pair( ".json", "application/json"));
    types.insert(std::make_pair( ".xml", "application/xml"));
    types.insert(std::make_pair( ".pdf", "application/pdf"));
    types.insert(std::make_pair( ".doc", "application/msword"));
    types.insert(std::make_pair( ".xls", "application/vnd.ms-excel"));
    types.insert(std::make_pair( ".ppt", "application/vnd.ms-powerpoint"));
    types.insert(std::make_pair( ".zip", "application/zip"));
    types.insert(std::make_pair( ".rar", "application/x-rar-compressed"));
    types.insert(std::make_pair( "", "application/octet-stream"));  // For generic binary data
    types.insert(std::make_pair( ".woff", "application/font-woff"));
    types.insert(std::make_pair( ".woff2", "application/font-woff2"));
    types.insert(std::make_pair( ".ttf", "application/font-ttf"));
    types.insert(std::make_pair( ".eot", "application/font-eot"));
    types.insert(std::make_pair( "", "multipart/form-data"));  // Used in form submissions with file uploads
    types.insert(std::make_pair( "", "application/x-www-form-urlencoded"));  // Used in HTML forms for URL-encoded data
}

void HttpMetaProvider::Methods( void )
{
    methods.push_back("GET");
    methods.push_back("POST");
    methods.push_back("DELETE");
    methods.push_back("PUT");
    methods.push_back("PATCH");
    methods.push_back("HEAD");
    methods.push_back("OPTIONS");
    methods.push_back("CONNECT");
    methods.push_back("TRACE");
    methods.push_back("COPY");
    methods.push_back("MOVE");
    methods.push_back("LINK");
    methods.push_back("UNLINK");
    methods.push_back("PURGE");
    methods.push_back("LOCK");
    methods.push_back("UNLOCK");
    methods.push_back("PROPFIND");
    methods.push_back("PROPPATCH");
}

std::string HttpMetaProvider::mimeType(std::string const &ext)
{
    std::string extension = ext.substr(ext.find_last_of("."));
    std::map<std::string, std::string>::iterator it = types.find(extension);
    if (it != types.end())
        return (it->second);
    else
        return ("application/octet-stream");
}

std::string HttpMetaProvider::httpMethod(std::string const &method)
{
    std::vector<std::string>::iterator it = methods.begin();
    while (it != methods.end())
    {
        if (*it == method)
            return (*it);
        it++;
    }
    return ("UNKNOWN");
}

