/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:30:12 by dmartiro          #+#    #+#             */
/*   Updated: 2023/12/08 02:27:15 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(const char *confFile)
{
    if (!confFile)
        throw HTTPCoreException("FILE ERROR: NULL is Not a file");
    IO.open(confFile, std::ios::in);
    if (!IO.is_open())
        throw HTTPCoreException("Error: File not found");
    context.push_back("server");
    context.push_back("location");

    directives.push_back("root");
    directives.push_back("index");
    directives.push_back("autoindex");
    directives.push_back("allow_methods");
    directives.push_back("error_page");
    directives.push_back("client_body_size");
    directives.push_back("listen");
    directives.push_back("server_name");
}

Parser::~Parser()
{
    
}

void Parser::start(ServerManager const *mgn)
{
    Parser::clean();
    Parser::scheme();
    Parser::semantic_analysis();
    Parser::intermediate_code_generation();
    Parser::syntax_analysis();
    Parser::fill_servers();
    std::list<Token>::iterator tok = tokens.begin();
    for(; tok != tokens.end(); tok++)
        std::cout << tok->type << " : " << tok->token << std::endl;
}

 void Parser::clean()
{
    std::string line;
    size_t comment = 0;
    while (std::getline(IO, line))
    {
        if (line.empty())
            continue;
        if ((comment = HTTPRequest::trim(line).find_first_of("#")) != std::string::npos)
        {
            line = line.substr(0, comment);
            config += (line.size() > 0) ? HTTPRequest::trim(line) + '\a' : "";
        }
        else
            config += HTTPRequest::trim(line) + '\a';
    }
    if (config.empty())
        throw HTTPCoreException("Error: File is Empty");
}

void Parser::semantic_analysis( void )
{
    for(size_t k = 0; k < server_ctx.size(); k++)
    {
        
        for(size_t i = 0, j = 0; i < server_ctx[k].size(); i++)
        {
            if(isWord(server_ctx[k][i]))
                addWord(server_ctx[k], &i);
            if (server_ctx[k][i] == '{')
                addToken(server_ctx[k][i], OPENBRACE);
            if (server_ctx[k][i] == '}')
                addToken(server_ctx[k][i], CLOSEBRACE);
            if (server_ctx[k][i] == ';')
                addToken(server_ctx[k][i], SEMICOLON);
            if (server_ctx[k][i] == '\a')
                addToken(server_ctx[k][i], SEPARATOR);
        }
    }
}

void Parser::intermediate_code_generation( void )
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
            if (next->type == OPENBRACE)
                ch->type = CONTEXT;
            if (next->type == SEPARATOR)
            {
                tmpNext = next;
                tmpNext++;
                if (tmpNext->type == OPENBRACE)
                    ch->type = CONTEXT;
            }
            if (next->type == SEMICOLON)
                ch->type = DIRECTIVE;
        }
    }
    ch = tokens.begin();
}


void Parser::syntax_analysis( void )
{
    std::list<Token>::iterator ch = tokens.begin();
    for(; ch != tokens.end(); ch++)
    {
        if (ch->type == WORD)
            throw HTTPCoreException(std::string("Config: Syntax error. ( " +  ch->token + " )").c_str());
        if (ch == tokens.begin())
        {
            if (ch->type != CONTEXT)
                throw HTTPCoreException(std::string("Config: Syntax error. ( " +  ch->token + " )").c_str());
        }
    }
}

void Parser::scheme( void )
{
    size_t brace = 0;
    std::string serverContext;
    std::vector<std::string> tmp_ctx;
    for(size_t i = 0; i < config.size(); i++)
    {
        if (config[i] == '{')
        {
            serverContext += config[i];
            brace++;
        }
        else if (config[i] == '}')
        {
            serverContext += config[i];
            if (brace == 0)
                throw HTTPCoreException("Config: Syntax error. ( { )");
            if (brace == 1)
            {
                server_ctx.push_back(serverContext);
                serverContext.clear();
            }
            brace--;
        }
        else
            serverContext += config[i];
    }
    if (brace > 0)
        throw HTTPCoreException("Config: Syntax error. ( } )");
    tmp_ctx = server_ctx;
    Parser::removeUnprintables(tmp_ctx);
    for(size_t i = 0; i < tmp_ctx.size(); i++)
        if (context_wrap(tmp_ctx[i]))
            throw HTTPCoreException("Config: In Server Context should not another server");
}

int Parser::context_wrap(std::string const &server)
{
    std::string srv = "server";
    size_t found = server.find(srv, 0);
    size_t counter = 0;
    while (found != std::string::npos)
    {
        if (server[found + 6] == '{')
            counter++;
        else if (std::isspace(server[found + 6]))
        {
            std::cout << "mta" << std::endl;
            size_t space_start = found + 6;
            size_t space_count = 0;
            while (server[space_start++] != '{')
                space_count++;
            std::string tmp = server.substr(found, found + space_count);
            remove_spaces(tmp);
            if (tmp == "server{")
                counter++;
        }
        found = server.find(srv, found + srv.size());
    }
    if (counter > 1)
        return (1);
    return (0);
}

void Parser::remove_spaces(std::string &tmp_text)
{
    for(size_t i = 0; i < tmp_text.size(); i++)
        if (std::isspace(tmp_text[i]))
        {
            tmp_text.erase(i, 1);
            --i;
        }
}

void Parser::fill_servers( void )
{
    // for(size_t i = 0; i < server_ctx.size(); i++)
    // {
    //     std::cout << server_ctx[i] << std::endl;
    // }
}

void Parser::removeUnprintables(std::vector<std::string> &tmp_ctx)
{
    for(size_t i = 0; i < tmp_ctx.size(); i++)
    {
        for(size_t k = 0; k < tmp_ctx[i].size(); k++)
            if (tmp_ctx[i][k] == '\a')
                tmp_ctx[i].erase(k, 1);
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

void Parser::addWord(std::string config, size_t *i)
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

void Parser::tolower(std::string &s)
{
    for(size_t i = 0; i < s.size(); i++)
        if (std::isupper(s[i]))
            s[i] = std::tolower(s[i]);
}