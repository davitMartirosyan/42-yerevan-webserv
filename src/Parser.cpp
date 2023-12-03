/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:30:12 by dmartiro          #+#    #+#             */
/*   Updated: 2023/12/04 00:46:35 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(std::string const &confFile)
{
    context.push_back("server\0");
    context.push_back("location\0");

    directives.push_back("root");
    directives.push_back("index");
    directives.push_back("autoindex");
    directives.push_back("allow_methods");
    directives.push_back("error_page");
    directives.push_back("client_body_size");
    directives.push_back("listen");
    directives.push_back("server_name");

    
    IO.open(confFile.c_str(), std::ios::in);
    if (!IO.is_open())
        throw HTTPCoreException("Error: File not found");
}

Parser::~Parser()
{
    
}

void Parser::start(ServerManager const *mgn)
{

    std::string config = Parser::trim_comments();
    Parser::semantics(config);
    Parser::correction();
    
    std::list<Token>::iterator tok = tokens.begin();
    for(; tok != tokens.end(); tok++)
        std::cout << tok->type << " : " << tok->token << std::endl;
}

std::string Parser::trim_comments()
{
    std::string line;
    std::string config;
    size_t comment = 0;
    while (std::getline(IO, line))
    {
        if (line.empty())
            continue;
        if ((comment = HTTPRequest::trim(line).find_first_of("#")) != std::string::npos)
        {
            line = line.substr(0, comment);
            config += (line.size() > 0) ? HTTPRequest::trim(line) : "";
        }
        else
            config += HTTPRequest::trim(line) + "\a";
    }
    std::cout << config << std::endl;
    std::cout << "***************************" << std::endl;
    if (config.empty())
        throw HTTPCoreException("Error: File is Empty");
    return (config);
}

void Parser::semantics(std::string const &config)
{
    for(size_t i = 0, j = 0; i < config.size(); i++)
    {
        if(isWord(config[i]))
            addWord(config, &i);
        if (config[i] == '{')
            addToken(config[i], OPENBRACE);
        if (config[i] == '}')
            addToken(config[i], CLOSEBRACE);
        if (config[i] == ';')
            addToken(config[i], SEMICOLON);
        if (config[i] == '\a')
            addToken(config[i], SEPARATOR);
    }
}

void Parser::correction( void )
{
    bool isSecond = false;
    std::list<Token>::iterator ch = tokens.begin();
    std::list<Token>::iterator next = ch;
    std::list<Token>::iterator tmpNext = ch;
    for(; ch != tokens.end(); ch++)
    {
        if (ch->type == WORD)
        {
            next = ch;
            ++next;
            if (next->type == OPENBRACE || (next->type == SEPARATOR && (++next)->type == OPENBRACE))
                ch->type = CONTEXT;
            else if (next->type == SEMICOLON || next->type == SEPARATOR)
                ch->type = DIRECTIVE;
        }
        //HERE
    }

    ch = tokens.begin();
    for(; ch != tokens.end(); ch++)
    {
        if (ch->type == OPENBRACE)
        {
            next = ch;
            ++next;
            if (next->type != DIRECTIVE && next->type != SEPARATOR)
                throw HTTPCoreException("Config: line error");
        }
        if (ch->type == DIRECTIVE)
        {
            next = ch;
            ++next;
            if (next->type != SEMICOLON)
                throw HTTPCoreException("Config: semicolon error");
        }
    }
}


void Parser::addToken(char s, p_type type)
{
    Token t;
    t.type = type;
    t.token = s;
    tokens.push_back(t);
}

bool Parser::isWord(char s)
{
    if (s != '{' && s != '}' && s != ';' && s != '\a')
        return (true);
    return (false);
}

void Parser::addWord(std::string const &config, size_t *i)
{
    int pos = *i;
    std::string wordpart;
    while (isWord(config[pos]))
    {
        wordpart += config[pos];
        pos++;
    }
    Token t;
    t.type = WORD;
    t.token = wordpart;
    tokens.push_back(t);
    *i = pos;
}

size_t Parser::contextOpen(std::string const &config, size_t p)
{
    size_t i = p;
    while (i < config.size())
    {
        
    }
    return (0);
}

size_t Parser::contextWord(std::string const &config, size_t p)
{
    size_t i = p;
    std::string contextWordPart;
    while (i < config.size())
    {
        if (config[i] == '{')
            break;
        contextWordPart += config[i];
        i++;
    }
    Token t;
    t.type = CONTEXT;
    t.token = contextWordPart;
    tokens.push_back(t);
    return (i);
}

bool Parser::isContext(std::string const &line)
{
    std::vector<std::string>::iterator it = std::find(context.begin(), context.end(), HTTPRequest::trim(line));
    if (it != context.end())
        return (true);
    return (false);
}

bool Parser::isDirective(std::string const &line)
{
    std::vector<std::string>::iterator it = std::find(directives.begin(), directives.end(), HTTPRequest::trim(line));
    if (it != directives.end())
        return (true);
    return (false);
}