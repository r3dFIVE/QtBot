# QtBot - Extensible Discord Bot

QtBot is an extensible Discord Chat bot written primarily in C++11 leveraging the Qt Framework for core functionality.

Additional functionality can be added via custom Qml objects called **BotScripts**.

*BotScripts* are custom Qml elements which provide access to the Discord API, as well as additional support for things like database access and file I/O.

1. [Building From Source](#building-from-source)
	* [Database Support](#database-support)	
	* [xml2json Support](#xml2json-support)
	* [Building on Windows 10](#building-on-windows-10)
	* [Building on Linux](#building-on-linux)
	* [Building on MacOS](#building-on-macos)
2. [Running QtBot](#running-qtbot)
	* [Running on Windows 10](#running-on-windows-10)
	* [Running on Linux](#running-on-linux)
	* [Running on MacOS](#running-on-macos)
3. [Adding Bot to Servers](#adding-bot-to-servers)
4. [Core Bot Commands](#core-bot-commands)
5. [Command Restrictions](#command-restrictions)
 	* [Default Restriction State](#default-restriction-state)
	* [Restriction Hierarchy](#restriction-hierarchy) 
6. [EventContext](#eventcontext)
7. [Discord API Calls](#discord-api-calls)
8. [Hello World Example Script](#hello-world-example-script)
	* [BotApi](#botapi)
	* [BotScript](#botscript)
	* [cCreateMessage](#ccreatemessage)
9. [Event Bindings]($event-bindings) 

# Building From Source

Qt Framework 5.15 is designed to run anywhere, thus QtBot will run on Windows, Linux, or MacOS. Currently there is only an installer for Windows. Installers for Linux and MacOS will come in later versions.

## Database Support

For MySQL/MariaDB and MongoDB support, the appropriate C/C++ connectors must be present on your development environment. 

### MySQLMariaDB

Instruction for configuring the Qt source to include MySQL/MariaDB support can be found here:

	https://doc.qt.io/qt-5/sql-driver.html#qmysql
	
### MongoDB
#### Windows

**Boost:**

MongoDB drivers require Boost library to function. Download newest release of Boost and copy to `<project_root>/lib/boost`. Remove/rename the boost folder to remove the release verionsoning, eg. `/boost_1_66_0/ -> /boost/`

**MongoDB C Driver:**

First you need to build the MongoDB C driver. Instructions can be found here:

	http://mongoc.org/libmongoc/current/installing.html
	
Once the build is done, copy the build output directoy (eg. `/mongo_c_driver`) to the `<project_root>/lib/` directory.

**MongoDB CXX Driver:**

The final step is building the MongoDB CXX driver. Instuctions can be found here:

	http://mongocxx.org/mongocxx-v3/installation/
	
Once the build is done, copy the build output directoy (eg. `/mongo_cxx_driver`) to the `<project_root>/lib/` directory.

#### Linux

## xml2json Support

xml2json header libarary is required for converting XML to Json to be used inside BotScripts

https://github.com/Cheedoong/xml2json

You can clone that project directly inside `<project_root>/lib`.

eg. `<project_root>/lib/xml2json`


## Building on Windows 10

Compiling on windows has been tested using MSVC2017 and MSVC2019.

### Prerequisites
1. Download and install "Build Tools" for either:
	* [Visual Studio 2017](https://my.visualstudio.com/Downloads?q=Visual%20Studio%202017)
	* [Visual Studio 2019](https://my.visualstudio.com/Downloads?q=Visual%20Studio%202019)
2. Download and install [Qt for Windows](https://www.qt.io/download-qt-installer):
	* Under **Qt**, select the following components:
		* Under **Qt 5.15.2**:
			1. MSVC 2019 64-bit - *(backwards compatible with 2017)*
			2. Sources - *(required for some database support)*
		* Under **Developer and Designer Tools**:
			1. Qt Creator CDB Debugger Support
			2. Debugging Tools for Windows
			3. Qt Creator Debug Symbols
			4. Qt Installer Framework 4.0 - *(only if you plan to build standalone installer)*
3. Download/clone QtBot source from git.

### Build from Qt Creator

1. Open *QtBot.pro* in Qt Creator.
	* If this is first time opening project, configure the project to use the *MSVC2019 64bit Kit*
	* Make sure to set an `install` make step if you want the required libaries to auto deploy to build folder.
2. Run qmake.
	* `Build -> Run qmake`
3. Build project
	* `Build -> Clean project "QtBot"`
	* `Build -> Build project "QtBot"`

### Build from Command Line

Instructions coming in 1.0.0 release!

## Building on Linux

### Prerequisites
1. Download and install `gcc`
	* **apt:** `apt-get install gcc`
	* **yum:** `yum install gcc`
2. Download and install [Qt for Linux](https://www.qt.io/download-qt-installer):
	* Under **Qt**, select the following components:
		* Under **Qt 5.15.0**:
			1. Desktop gcc 64-bit
			2. Sources - *(required for some database support)*
		* Under **Developer and Designer Tools**:
			1. Qt Creator 4.13.3 Debug Symbols
			2. Qt Installer Framework 4.0 - *(only if you plan to build standalone installer)*
			3. CMake 3.19.0
			4. Ninja 1.10.0
3. Download/clone QtBot source from git.

### Build from Qt Creator

1. Open *QtBot.pro* in Qt Creator.
	* If this is first time opening project, configure the project to use the *Desktop Qt 5.15.0 GCC 64bit* Kit.
2. Run qmake.
	* `Build -> Run qmake`
3. Build project.
	* `Build -> Clean project "QtBot"`
	* `Build -> Build project "QtBot"`

### Build from Command Line

Instructions coming in 1.0.0 release!

## Building on MacOS

Instructions coming in 1.0.0 release!

# Running QtBot

QtBot can be run directly from Qt Creator or from the target build directory if you built from source. QtBot can also be installed and run the traditional way via offline installation package.

## Prerequisites

1. A valid bot account with bot token from [Discord](https://discord.com/developers/applications).
2. A valid [settings.ini](https://github.com/r3dFIVE/QtBot/blob/master/bot/settings.ini) file correctly filled out.
3. QtBot installed via installer, or compiled from source!

## Running on Windows 10
### From Qt Creator
1. Open *QtBot.pro* in Qt Creator, configure kit if needed.
2. Add a valid [settings.ini](https://github.com/r3dFIVE/QtBot/blob/master/bot/settings.ini) file to command line arguments:
	1. Select "Projects" from left pane.
	2. Add `-s %%path_to%%\settings.ini` to *Command line arguments* for your kit.
		* `%%path_to%%` being a valid path to settings.ini.
3. Build project `Build -> Build project "QtBot"`
4. Run QtBot `Build -> Run`

### From Command Line
**Via Installer**:
1. Fill out settings.ini file at `%%qtbot_install_dir%%\config`
	* `%%qtbot_install_dir%%` being the install directory for QtBot
2. Run QtBot!
	* From Start Menu `QtBot.lnk`
	* From install directory `bot.exe`

## Running on Linux 
### From Qt Creator
1. Open *QtBot.pro* in Qt Creator, configure kit if needed.
2. Add a valid [settings.ini](https://github.com/r3dFIVE/QtBot/blob/master/bot/settings.ini) file to command line arguments:
	1. Select "Projects" from left pane.
	2. Add `-s /path/to/settings.ini` to *Command line arguments* for your kit.
		* `/path/to/` being a valid path to settings.ini.
3. Build project `Build -> Build project "QtBot"`
4. Run QtBot `Build -> Run`

### Fom Command Line
Instructions coming in version 1.0.0!

##  Running on MacOS
Instructions coming in version 1.0.0!

# Adding Bot to Servers
You must create an OAuth2 link to give to server/guild admins so they can invite your bot to their server/guild. This must be done manually at the moment as the bot does not currently support generating one on command.

Creating valid OAuth2 links is done in your Bot's application profile on the `OAuth2` page, https://discord.com/developers

**eg.**
`https://discordapp.com/oauth2/authorize?client_id=<bot_id>&scope=bot&permissions=-9`

`<bot_id>` being your bot application's user id.

# Core Bot Commands
There are several "core" bot commands that come hard coded. These do not require a script to run.

Core commands only affect the guild they were issued in with the exception of `.reload`.

 Any `.reload` commands sent to the Bot via direct message, will reload ALL guilds. This requires **Bot Owner** privilege to be set in the `settings.ini` file for the given user. Individual guild Bot Admins assigned via admin role cannot reload all guilds. 
 
| Command | Requires Admin | Description |
|---|---|---|
| .reload | true | `.reload` will reload all scripts. This will rebuild scripts from the Bot's script directory, clearing any cached script data in the process.<br> **If the Bot Owner issues this command via direct message with the Bot, then **all** guilds will be reloaded.|
| .enable | true | `.enable <name> <id>` will enable an entire script, if a script \<name> or an individual command if a command \<name> is provided for the given \<id> |
| .disable | true | `.disable <name> <id>` will disable an entire script, if a script \<name> or an individual command if a command \<name> is provided for the given \<id> |
| .timed | false | `.timed` will display all started and stopped timed jobs for the current guild. |
| .timedstop | true | `.timedstop <timed_job_number>` will stop the timed job specified by \<timed_job_number>.<br><timed_job_number> can be retrieved from the `.timed` command.  |
| .timedstart | true | `.timedstart <timed_job_number>` will start/resume a *stopped* timed job. This has no affect on already running timed jobs.<br><timed_job_number> can be retrieved from the `.timed` command. |
| .timedrestart| true | `.timedrestart <timed_job_number>` will restart a stopped or started timed job. This will effectively set the elapsed time back to zero for the specified timed job. |

# Command Restrictions
## Default Restriction State
Commands will either be enabled or disabled by default, depending on the value set for `restriction_state` in your `settings.ini` file.
 1. enabled  ->  All scripts/commands (non-admin) enabled by default.
 2. disabled  ->  All scripts/commands (non-admin) disabled by default.
## Restriction Hierarchy
Command restriction states can be further fine-tuned via the `.enable` and `.disable` commands. Both `.enable` and `.disable` take two parameters, `<name>` and `<id>`.
 * `<name>`: Can  either an individual command name, or a script name. If a script name is given, then all of its registered commands will be affected. If an individual command name is given, then only that command will be affected.
 * `<id>`: Is the snowflake ID of your target for the .`enable/disable` command. Valid IDs sources are User ID, Role ID, Channel ID or Guild ID.

The bot will check if a command has been explicitly enabled or disabled in the following order:
 1. User ID
 2. Role ID
 3. Channel ID
 4. Guild ID
 5. Default Restriction State *(from settings file)*

For example, if a command has been **disabled** for a specific `channel_id` but **enabled** for a specific `user_id`, then that user can still user the command in the disabled channel.
If a command has been **enabled** for a specific `channel_id` but **disabled** for a specific `user_id`, then that user will not be able to use the command, even in the enabled channel.

# EventContext
**More detailed information coming in 1.0.0!**

EventContext contains all the contextual data for your bound Discord event. The most common of Discord Event will be `MESSAGE_CREATE` which is sent any time a user posts a message such as issuing Bot commands.

| Property Name | Type | Description|
| --- | ---| --- | 
| source_payload | Object | The entire source payload that triggered this binding. Can be used when you need more information. |
| target_payload | Object | Your JSON object you will be sending to the Discord API.|
| content | String | The `content` field, if exists, from `source_payload`. This is the field that would contain the entire message a user posted.|
| args | String[] | This is the `content` field, if exists, split into an array of strings. Useful for parsing arguments from commands. |
| author  | Object | Contains useful fields such as `username` |
| user_id | String | This field represents the source/target `user_id` for the context. This will be set by default to the `author`'s `user_id`, if exists.<br> When passed to an API route that requires a `user_id`, this field will be used and required.|
| channel_id | String | This field represents the source/target `channel_id` for the context. This will be set by default to the `channel_id` the command was issued from.<br> When passed to an API route that requires a `channel_id`, this field will be used and required.|
| guild_id | String | This field represents the source/target `guild_id` for the context. This will be set by default to the `guild_id` the command was issued from, if exists.<br> When passed to an API route that requires a `guild_id`, this field will be used and required.|

# Discord API Calls
**MUCH more detailed information coming in 1.0.0!!**

All Bot Discord API Calls take exactly one parameter, the EventContext object.

## Channel API Calls
Bot has access to all channel related Discord API calls.
https://discord.com/developers/docs/resources/channel
| Bot Function Name | Discord API Documentation |
| --- | --- |
| `cCreateMessage` | https://discord.com/developers/docs/resources/channel#create-message |

## Guild API Calls
Bot has access to all guild related Discord API calls.
https://discord.com/developers/docs/resources/guild
| Bot Function Name | Discord API Documentation |
| --- | --- |
| `gModifyGuildMember` | https://discord.com/developers/docs/resources/guild#modify-guild-member |
# Hello World Example Script
It would be easiest to show an simple script and explain what is happening!

**hello.qml**
```javascript
import BotApi 1.0

BotScript {
	name: "helloWorld"
	
	commands: {
		".hello" : "world"		
	}
	
	function world(context) {				
		context.target_payload.content = `Hello ${context.author.username}, to my bot world!`  
		cCreateMessage(context)
	}
}
```
When this script is loaded, users will now be able to issue the `.hello` command, which would have the bot user (QtBOT) to respond accordingly.
```
[9:18 AM] r3dFIVE: .hello
[9:18 AM] QtBOT: Hello r3dFIVE, to my bot world!
```

## BotApi
Each QML script must import the Bot API module to enable use of all the bot features inside your script.
```javascript
import BotApi 1.0
```
## BotScript
BotScript is the custom Qml element built specifically for QtBot. To be considered a "valid" BotScript, it must have a unique script `name` and at least one `command` binding. Each command binding key must be unique across **all** scripts. 
```javascript
BotScript {
	name: "helloWorld"
	commands: {
		".hello" : "world"		
	}
	...
}
```
The key/value pair for `commands` relates to `<command_name>  :  <function_name>`. In this example, `.hello` maps to the JavaScript function `function world(context) { }`. Your mapped functions must take exactly one parameter, it does not need to be named *context*.
**EventContext** is the object passed into your mapped function containing all the relevant data needed for your API calls.


## cCreateMessage
```javascript
function world(context) {				
		context.target_payload.content = `Hello ${context.author.username}, to my bot world!`  
		cCreateMessage(context)
	}
```
From our example above:
```javascript
context.target_payload.content = `Hello ${context.author.username}, to my bot world!`  
```
We set the `content` field of the `context`'s `target_payload` to be sent to the Discord API which will then be posted back in the channel it was issued from based on `channel_id`.

The `content` field's response string also gets the `author.username` from the event `context` to dynamically populate the field based on whichever user *(author)* issued the command.

Finally, in our example, we send the `context` to the Discord API using the [Channel Create Message](https://discord.com/developers/docs/resources/channel#create-message) endpoint via bot function `cCreateMessage`.
```javascript
cCreateMessage(context)
```
Full list of API functions is listed [here](#discord-api-calls)

# Event Bindings

Event Bindings are a more advanced ways to bind functionality than the simple `1:1 functionName to CommandName` command mapping.

There are three kinds of event bindings to which you can bind BotScript functions. 

1. Gateway Events
2. Command Events
3. Timed Events

In the previous `Hello World!` example, we used the simple `commands` mapping of command name to function name. These will actually get converted into Command Events.

## Gateway Events

Gateway Events are any [Gateway Events](https://discord.com/developers/docs/topics/gateway#commands-and-events-gateway-events) sent from Discord. Gateway events are sent from discord as they happen in your joined guilds.


| Property Name | Type | Default | Required | Description |
|---|---|---|---|---|
| binding_type | String |  | true | The type of binding: `gateway`, `command`, `timed`. |
| binding_name | String |  | true | The unique name of binding, cannot be same as other script, command or binding names. |
| gateway_event | String |  | true | The specific [Gateway Event](https://discord.com/developers/docs/topics/gateway#commands-and-events-gateway-events) you want to bind to. |
| function | String |  | true | The name of the function you want to call. |
| ignore_admin | bool | false | false | If set to `true`, event will ignore admin privileges in invocation checks. This allows events to be disabled that would otherwise automatically be invoked due to admin privileges.  |
| singleton | bool | false | false | Do you only want this event to be run once independent of specific guilds `GuildId = 0` |
| description | String |  | false | The description, if any, you wish the help dialog to display. |

Eg.

```javascript
event_bindings: [
	{ 
	  "binding_type" : "gateway",
	  "binding_name" : "someUniqueName",
      "gateway_event" : "MESSAGE_DELETE",
      "function" : "someFunctionName",
	  "ignore_admin" : "true",	  
	  "singleton" : false, 
	  "description" : "This is a description that will get shown in the help dialog!" 
	}
]
```

## Command Events

Command Events are a special kind of Gateway Events (MESSAGE_CREATE) which allows you to bind specific user commands to BotScript functions. QtBot will check the first word of MESSAGE_CREATE events for valid BotScript commands.


| Property Name | Type | Default | Required | Description |
|---|---|---|---|---|
| binding_type | String |  | true | The type of binding: `gateway`, `command`, `timed`. |
| command | String |  | true | The command you want to bind your BotScript function to. |
| function | String |  | true | The name of the function you want to call. |
| admin_only | bool | false | false | If set to `true`, this will only be invocable by Bot Admins  |
| description | String |  | false | The description, if any, you wish the help dialog to display. |

Eg.

```javascript
event_bindings: [
	{ 
	  "binding_type" : "command",
      "command" : ".somecommand",
      "function" : "someFunctionName",
	  "admin_only" : true,	  
	  "description" : "This is a description that will get shown in the help dialog!" 
	}
]
```

## Timed Events

Timed events are QtBot's equivalent of task scheduling. Timed events can be used to call bot functions after a specified duration, either once (singleshot), or repeatedly.

Timed Events are not standard Gateway Events, as such, they do not have a default populated EventContext. EventContext objects are typically populated from the incoming Gateway Events. In lie of such, you are able to create your own context and attach it to the Timed Binding. This will be used as the EventContext when making the bound BotScript function calls.


| Property Name | Type | Default | Required | Description |
|---|---|---|---|---|
| binding_type | String |  | true | The type of binding: `gateway`, `command`, `timed`. |
| function | String |  | true | The name of the function you want to call. |
| fire_after | Number |  | true  | The number of seconds this timed event should execute after.  |
| single_shot | bool | false | false | Set to `true` if this event should only fire once.  |
| context | EventContext |  | false | The EventContext you wish to call your BotScript function with.  |
| description | String |  | false | The description, if any, you wish the help dialog to display. |

Eg.

```javascript
event_bindings: [
	{ 
	  "binding_type" : "timed",
      "function" : "someFunctionName",
	  "fire_after" : 42,
	  "single_shot" : false,
	  "context" : aValidContextObject,
	  "description" : "This is a description that will get shown in the help dialog!" 
	}
]
```
