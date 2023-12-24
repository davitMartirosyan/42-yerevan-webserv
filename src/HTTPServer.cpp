/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:57:39 by dmartiro          #+#    #+#             */
/*   Updated: 2023/12/24 17:14:09 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPServer.hpp"
#include <unordered_map>
#include "HelperFunctions.hpp"
#include "Cgi.hpp"
#include "EvManager.hpp"
#include "InnerFd.hpp"
#include "Types.hpp"

size_t longestMatch(std::string const &s1, std::string const &s2);

HTTPServer::HTTPServer( void )
{
    //defualt initializations
    this->port = DEFAULT_HTTP_PORT;
    this->ip = DEFAULT_MASK;
    methodsMap["GET"] = &HTTPServer::get;
    methodsMap["POST"] = &HTTPServer::post;
    methodsMap["DELETE"] = &HTTPServer::del;
    //boundary = "&"; // !IMPORTANT: if GET request: the boundary is (&) else if POST request: boundary is read from (Headers)
    methods.push_back("GET");
    methods.push_back("POST");
    methods.push_back("DEL");
}

HTTPServer::~HTTPServer()
{
    
}

void HTTPServer::setPort(std::string const &port)
{
    if (port.size() > 5)
        throw HTTPCoreException("Port: is to long");
    for(size_t i = 0; i < port.size(); i++)
        if (!std::isdigit(port[i]))
            throw HTTPCoreException("Port: Non digit character");
    this->n_port = (uint16_t)std::atoi(port.c_str());
    this->port = port;
}

const char* HTTPServer::getPort( void ) const
{
    return (port.c_str());
}

const char* HTTPServer::getIp( void ) const
{
    return (this->ip.c_str());
}

uint16_t HTTPServer::getNPort( void ) const
{
    return (this->n_port);
}

uint32_t HTTPServer::getNIp( void ) const
{
    return (this->n_ip);
}

void HTTPServer::setIp(std::string const &ipv)
{
    size_t n = 0;
    size_t k = 0;
    std::string octet;
    
    if (ipv.size() > 15)
        throw HTTPCoreException("The entered IP address does not follow the correct syntax.");
    for(size_t i = 0; i <= ipv.size(); i++)
    {
        if (std::isdigit(ipv[i]))
        {
            n++;
            octet += ipv[i];
        }
        else if (ipv[i] == '.' || i >= ipv.size())
        {
            if (ipv[i] == '.')
                k++;
            if (n > 3 || std::atoi(octet.c_str()) > 255)
                throw HTTPCoreException("The entered IP address does not follow the correct syntax.");
            octet.clear();
            n = 0;
        }
        else
            throw HTTPCoreException("The entered IP address does not follow the correct syntax.");

    }
    if (k != 3)
        throw HTTPCoreException("The entered IP address does not follow the correct syntax.");
    this->ip = ipv;
}

void HTTPServer::push(std::string const &prefix, Location locationDirective)
{
    this->locations.insert(std::make_pair(prefix, locationDirective));
}


void HTTPServer::push__serverName(std::string const &srvName)
{
    std::vector<std::string>::iterator it = std::find(_serverName.begin(), _serverName.end(), srvName);
    if (it == _serverName.end())
        _serverName.push_back(srvName);
}

const Location* HTTPServer::find(std::string const &prefix) const
{
    std::string path = prefix;
    size_t sl = HTTPRequest::slashes(path);
    for(size_t i = 0; i <= sl; i++)
    {
        std::map<std::string, Location>::const_iterator route = locations.find(path);
        if (route != locations.end())
            return (&route->second);
        path = path.substr(0, path.find_last_of("/"));
    }
    return (NULL);
}

std::vector<std::string> const &HTTPServer::get_serverNames( void ) const
{
    return (_serverName);
}

std::map<std::string, Location> const &HTTPServer::getLocations( void ) const
{
    return (locations);
}


sock_t HTTPServer::getfd( void ) const
{
    return (this->_fd);
}

void HTTPServer::up()
{
    const char* givenIp = ip.c_str();
    const char* givenPort = port.c_str();
    Tcp::setup(givenIp, givenPort);
    Tcp::createSocket();
    Tcp::bindSocket();
    Tcp::listenSocket();
    std::cout << givenIp <<  ":" << givenPort << std::endl;
    freeaddrinfo(addrList);
}

void HTTPServer::push(sock_t clFd, Client *clt)
{
    clnt.insert(std::make_pair(clFd, clt));
}

void HTTPServer::push(HTTPServer &srv) {
    _srvs.push_back(srv);
};

HTTPServer *HTTPServer::getSubServerByName(std::string const &serverName) {
    for (size_t i = 0; i < _srvs.size(); ++i) {
        const std::vector<std::string> &srvNames =  _srvs[i].get_serverNames();
        std::vector<std::string>::const_iterator it = std::find(srvNames.cbegin(),srvNames.cend(), serverName);
        if (it != srvNames.end()) {
            return (&_srvs[i]);
        }
    }
    return (NULL);
};

// int HTTPServer::pop(sock_t clFd)
// {
//     std::map<sock_t, Client*>::iterator it = clnt.find(clFd);
//     if (it != clnt.end())
//     {
//         delete it->second;
//         clnt.erase(it);
//         return (0);
//     }
//     return (-1);
// }

bool HTTPServer::exist(sock_t fd)
{
    return (clnt.find(fd) != clnt.end());
}


bool HTTPServer::operator==(HTTPServer const &sibling) const
{
    if (std::strcmp(this->getIp(), sibling.getIp()) == 0 \
        && std::strcmp(this->getPort(),sibling.getPort()) == 0)
      return (true);  
    return (false);
}

bool HTTPServer::operator==(sock_t fd) const
{
    if (clnt.find(fd) != clnt.end()) {
      return (true);
    } 
    return (false);
}

Client* HTTPServer::getClient(sock_t fd)
{
    std::map<sock_t, Client*>::iterator it = clnt.find(fd);
    if (it != clnt.end())
        return (it->second);
    return (NULL);
}

void HTTPServer::removeClient(sock_t fd)
{
    std::map<sock_t, Client*>::iterator it = clnt.find(fd);
    if (it != clnt.end()) {
        delete it->second;
        clnt.erase(it);
    }
    return ;
}


InnerFd *HTTPServer:: getInnerFd(int fd) {
    std::map<int, InnerFd *  >::iterator it = _innerFds.find(fd);
    if (it != _innerFds.end()) {
        return(it->second);
    }
    for (size_t i = 0; i < _srvs.size(); ++i) { // TODO check it
        std::map<int, InnerFd *  >::iterator it = _srvs[i]._innerFds.find(fd);
        if (it != _innerFds.end()) {
            return(it->second);
        }
    }
    return (NULL);
};

void HTTPServer::addInnerFd(InnerFd *obj) {
    _innerFds.insert(std::pair<int, InnerFd *>(obj->_fd, obj));
};

void HTTPServer::removeInnerFd(int fd) {
    std::map<int, InnerFd *>::iterator it = _innerFds.find(fd);
    if (it != _innerFds.end()) {
        delete it->second;
    }
    _innerFds.erase(fd);
};


const Location* HTTPServer::findMatching(std::string const &realPath) const
{
    std::map<std::string, Location>::const_iterator loc;
    std::map<std::string, Location>::const_iterator match;
    size_t longestMatchSize = 0;
    size_t currentMatch = 0;
    for(loc = locations.begin(); loc != locations.end(); loc++)
    {
        currentMatch = longestMatch(loc->first, realPath);
        if (longestMatchSize < currentMatch)
        {
            match = loc;
            longestMatchSize = currentMatch;
        }
        else if (longestMatchSize == currentMatch)
        {
            if (match->first < loc->first)
                match = loc;
        }
    }
    return (&match->second);
}

size_t longestMatch(std::string const &s1, std::string const &s2)
{
    size_t match = 0;
    for(size_t i = 0; i < s1.size(); i++)
    {
        if (s1[i] != s2[i])
            break;
        match++;
    }
    return (match);
}

void HTTPServer::get(Client &client) {
    const std::string &path = client.getPath();

    if (access(path.c_str(), R_OK) == 0) {
        std::string fileContent;
        if (client.isCgi() == true) {
            int fd = Cgi::execute(client);
            client.setCgiPipeFd(fd);
        } else {
                if (this->getAutoindex() == true && HTTPRequest::isDir(path)) {
                    client.setBody(directory_listing(path, client.getDisplayPath()));
                } else if (HTTPRequest::isDir(path)) {
                    throw ResponseError(404, "not found");
                } else {
                    int fd = open(path.c_str(), O_RDONLY);
                    if (fd == -1) {
                        throw ResponseError(500, "Internal Server Error");
                    }
                    EvManager::addEvent(fd, EvManager::read);
                    this->addInnerFd(new InnerFd(fd, client, client.getResponseBody(),  EvManager::read));
                }
            std::map<std::string, std::string>::iterator mime = Types::MimeTypes.find(client.getExtension());
            std::string mimeType;
            if (mime != Types::MimeTypes.end())
                mimeType = mime->second;
            else
                mimeType = "text/plain";
            
            
            client.addHeader(std::pair<std::string, std::string>("Content-Type", mimeType));
            // client.addHeader(std::pair<std::string, std::string>("Content-Type", "text/" + client.getExtension()));
        }
    } else {
        throw ResponseError(404, "not found");
    }
};

void HTTPServer::post(Client &client) {
    const std::string &path = client.getPath();
    
    std::cout << "\n--- in Post function \n" << std::endl;
    std::cout << "path = " << path << std::endl;
    if (client.isCgi() == true) {
        int fd = Cgi::execute(client);
        client.setCgiPipeFd(fd);
    } else {
        std::unordered_map<std::string, std::string> &uploadedFiles = client.getUploadedFiles();
        std::unordered_map<std::string, std::string>::iterator it = uploadedFiles.begin();
        for (; it != uploadedFiles.cend(); ++it) {
            const std::string &fileName = it->first;
            std::string &fileContent = it->second;
            int fd = open((client.getSrv().getUploadDir() + fileName).c_str(),  O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
            if (fd == -1) {
                throw ResponseError(500 , "Internal Server Error");
            }
            EvManager::addEvent(fd, EvManager::write);
            this->addInnerFd(new InnerFd(fd, client, fileContent, EvManager::write));
        }
    }
    client.addHeader(std::pair<std::string, std::string>("Content-type", "text/html"));
};

void HTTPServer::del(Client &client) {
    if (std::remove(client.getPath().c_str()) == -1) {
        throw ResponseError(404, "not found");
    };
};

void HTTPServer::processing(Client &client)
{
    std::map<std::string, void (HTTPServer::*)(Client&)>::iterator function = methodsMap.find(client.getMethod());
    if (function != methodsMap.end() && this->findMethod(client.getMethod()) != NULL)
    {
       (this->*(function->second))(client);
    } else {
        throw ResponseError(405, "Method Not Allowed");
    }
}

std::string	HTTPServer::directory_listing(const std::string &path, std::string displayPath)
{
	DIR					*opened_dir;
	dirent				*dir_struct;
	std::string			table;
	std::string			name;
	struct stat			buf;
	struct tm			*timeinfo;
	char				time_buf[100];
	std::string 		relPath;
	
	if (path != "." && path != ".." && path[0] != '/' && (path[0] != '.' && path[1] != '/') && (path[0] != '.' && path[1] != '.' && path[2] != '/')) {
        relPath = "./" + path + "/";
    } else {
		relPath = path + "/";
	}

	opened_dir = opendir(relPath.c_str());
	
    if (opened_dir == NULL) {
        throw std::logic_error (strerror(errno));
    }

	table += "<!DOCTYPE html><html><head><title>";
	table += "Index of ";
	table += displayPath;
	table += "</title>";
	table += "<style>";
	table += ".box>* {flex: 33.33%;}";
	table += ".box {display: flex; flex-wrap: wrap; width: 75%;}";
	table += "</style></head>";
	table += "<body><h1>";
	table += "Index of ";
	table += displayPath;
	table += "</h1><hr><pre class=\"box\">";

	dir_struct = readdir(opened_dir);
	while ((dir_struct = readdir(opened_dir)) != NULL)
	{
		name = dir_struct->d_name;
		if (name != ".")
		{
			table += "<a href=\"";
            if (displayPath.back() != '/')
            {
    			displayPath +=  "/";
            }
			table += displayPath + name;
			table += "\">";
			table += name;
			table += "</a>";
			if (stat((relPath + name).c_str(), &buf) == 0)
			{
				table += "<span>";
				timeinfo = localtime(&(buf.st_mtime));
				strftime(time_buf, 100, "%d-%b-%Y %H:%S", timeinfo);
				table += time_buf;
				table += "</span><span>";
				if (dir_struct->d_type == DT_DIR)
					table += "-";
				table += "</span>";
			}
			table += "<br>";
		}
	}
	table += "</pre><hr></body></html>";
	closedir(opened_dir);
    return table;
}