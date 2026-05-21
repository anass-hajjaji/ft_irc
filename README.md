# ft_irc

Minimal IRC server implementation written in C++98. It supports basic IRC registration, channels, and core commands, plus an optional bonus bot.

## Features
- PASS/NICK/USER registration flow
- Private messages to users or channels
- Channel management (JOIN, INVITE, KICK, TOPIC)
- Channel modes: invite-only (+i), topic-restricted (+t), key/password (+k), user limit (+l), operator (+o)
- Bonus: simple IRC bot with helper commands

## Build
```sh
make
```

### Bonus bot
```sh
make bonus
```

## Run
```sh
./ircserv <port> <password>
```

Constraints:
- Port must be in the range 1024–65535
- Password must be at least 3 characters and only contain alphanumeric characters or `_`

## Connect (example with a generic IRC client)
After connecting to the server, register in this order:
```text
PASS <password>
NICK <nickname>
USER <username> <hostname> <servername> :<realname>
```

## Supported commands
- `PRIVMSG <nick>|<channel> :<message>`
- `JOIN <#channel>[,<#channel>...] [key1,key2,...]`
  - `JOIN 0` leaves all channels
- `MODE <#channel> [modes] [params]`
  - `+i` invite-only, `+t` topic restriction, `+k` channel key, `+l` user limit, `+o` operator
- `KICK <#channel> <nick>[,<nick>...] :<reason>`
- `INVITE <nick> <#channel>`
- `TOPIC <#channel> [:<topic>]`

## Bonus bot
Run the bot after building it:
```sh
./ircserv_bot <ip> <port> <password> <bot_nick>
```

The bot accepts direct `PRIVMSG` commands:
- `hello` – welcome message
- `help` – list commands
- `time` – current time
- `quote` – random quote
- `echo <message>` – echoes the message
