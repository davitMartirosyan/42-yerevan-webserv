/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:29:55 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/21 19:16:31 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client( void )
{
    this->rd = 0;
}

Client::Client(sock_t clfd, sock_t srfd)
{
    this->fd = clfd;
    this->serverFd = srfd;
    this->rd = 0;
}

Client::Client(sock_t clfd)
{
    this->fd = clfd;
    this->serverFd = -1;
}

sock_t Client::getFd( void ) const
{
    return (this->fd);
}

sock_t Client::getServerFd( void ) const
{
    return (this->serverFd);
}

Client::~Client()
{
}


void Client::appendRequest( void )
{
    bool reqLineFound = 0;
    bool headersFound = 0;
    size_t space = 0;
    char *buf = new char[READ_BUFFER];
    std::cout << "es hasa" << std::endl;
    while (1)
    {
        if ((rd = recv(fd, buf, sizeof(READ_BUFFER), 0)) > 0)
        {
            buf[rd] = '\0';
            httpRequest.append(buf, rd);
            if ((reqLineEnd = httpRequest.find_first_of("\r\n")) != std::string::npos && !reqLineFound)
            {
                request = httpRequest.substr(0, reqLineEnd);
                for (size_t i = 0; i < request.size(); i++)
                    if (std::isspace(request[i]))
                        space++;
                if (space == 2)
                {
                    method = trim(request.substr(0, request.find_first_of(" ")));
                    request.erase(0, request.find_first_of(" ") + 1);
                    path = trim(request.substr(0, request.find_first_of(" ")));
                    request.erase(0, request.find_first_of(" ") + 1);
                    version = trim(request.substr(0, request.find("\r\n")));
                    reqLineFound = 1;
                    httpRequest.erase(0, reqLineEnd + 2);
                }
            }
            if ((bodyEnd = httpRequest.find("\r\n\r\n")) != std::string::npos && !headersFound)
            {
                std::stringstream iss(httpRequest);
                std::string get_next_line;
                while (std::getline(iss, get_next_line) && get_next_line != "\r\n")
                {
                    size_t colon;
                    if ((colon = get_next_line.find_first_of(":")) != std::string::npos && std::isspace(get_next_line[colon+1]))
                    {
                        std::string key = trim(get_next_line.substr(0, colon));
                        std::string value = trim(get_next_line.substr(colon+2, get_next_line.find("\r\n")));
                        httpHeaders.insert(std::make_pair(key, value));
                    }
                }
                httpRequest.erase(0, bodyEnd + 4);
                headersFound = 1;
            }
        }
        else
            break;
    }
    delete [] buf;
    if (reqLineFound && headersFound)
    {
        if (!method.empty())
            HTTPRequest::processing(fd);
        reqLineFound = false;
        headersFound = false;
    }
}

