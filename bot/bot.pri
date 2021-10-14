QT += gui websockets sql qml

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.


win32 {
    LIB_DIR = $$PWD/../lib
    BOOST_HEADERS=$$LIB_DIR/boost
    MONGO_CXX_HEADERS=$$LIB_DIR/mongo-cxx-driver/include
    MONGO_CXX_LIB=$$LIB_DIR/mongo-cxx-driver/lib

    INCLUDEPATH += $$MONGO_CXX_HEADERS/mongocxx/v_noabi
    INCLUDEPATH += $$MONGO_CXX_HEADERS/bsoncxx/v_noabi
    INCLUDEPATH += $$BOOST_HEADERS

    LIBS += -L$$MONGO_CXX_LIB -lmongocxx -lbsoncxx
} else {
    LIBS += -L/usr/local/lib -lmongocxx -lbsoncxx
    INCLUDEPATH += /usr/local/include/bsoncxx/v_noabi
    INCLUDEPATH += /usr/local/include/mongocxx/v_noabi
}


HEADERS += \
    $$PWD/botjob/commandbinding.h \
    $$PWD/botjob/databasecontext.h \
    $$PWD/botjob/gatewaybinding.h \
    $$PWD/botjob/ibinding.h \
    $$PWD/botjob/job.h \
    $$PWD/botjob/jobqueue.h \
    $$PWD/botjob/scriptbuilder.h \
    $$PWD/botjob/timedbinding.h \
    $$PWD/botjob/timedjobs.h \
    $$PWD/entity/commandrestrictions.h \
    $$PWD/entity/idbmanager.h \
    $$PWD/entity/mongoconnectionpool.h \
    $$PWD/entity/mongomanager.h \
    $$PWD/entity/sqlmanager.h \
    $$PWD/entitymanager.h \
    $$PWD/payloads/activityemoji.h \
    $$PWD/bot.h \
    $$PWD/eventhandler.h \
    $$PWD/gateway.h \
    $$PWD/logging/logcontext.h \
    $$PWD/logging/logfactory.h \
    $$PWD/logging/logger.h \
    $$PWD/logging/logworker.h \
    $$PWD/payloads/activity.h \
    $$PWD/payloads/activityassets.h \
    $$PWD/payloads/attachment.h \
    $$PWD/payloads/channelmention.h \
    $$PWD/payloads/embed.h \
    $$PWD/payloads/embedauthor.h \
    $$PWD/payloads/embedfield.h \
    $$PWD/payloads/embedfooter.h \
    $$PWD/payloads/embedmedia.h \
    $$PWD/payloads/eventcontext.h \
    $$PWD/payloads/guildroledelete.h \
    $$PWD/payloads/guildroleupdate.h \
    $$PWD/payloads/invalidsession.h \
    $$PWD/payloads/activityparty.h \
    $$PWD/payloads/activitysecrets.h \
    $$PWD/payloads/activitytimestamps.h \
    $$PWD/payloads/channel.h \
    $$PWD/payloads/clientstatus.h \
    $$PWD/payloads/emoji.h \
    $$PWD/payloads/gatewaypayload.h \
    $$PWD/payloads/guild.h \
    $$PWD/payloads/guildmember.h \
    $$PWD/payloads/hello.h \
    $$PWD/payloads/gatewaypayload.h \
    $$PWD/payloads/hello.h \
    $$PWD/payloads/heartbeat.h \
    $$PWD/payloads/identify.h \
    $$PWD/payloads/identifyproperties.h \
    $$PWD/payloads/jsonserializable.h \
    $$PWD/payloads/message.h \
    $$PWD/payloads/messageactivity.h \
    $$PWD/payloads/messageapplication.h \
    $$PWD/payloads/messagereference.h \
    $$PWD/payloads/permissionoverwrite.h \
    $$PWD/payloads/presenceupdate.h \
    $$PWD/payloads/ratelimit.h \
    $$PWD/payloads/reaction.h \
    $$PWD/payloads/ready.h \
    $$PWD/payloads/resume.h \
    $$PWD/payloads/role.h \
    $$PWD/payloads/updatestatus.h \
    $$PWD/payloads/user.h \
    $$PWD/payloads/voicestate.h \
    $$PWD/botjob/botscript.h \
    $$PWD/qml/enums/networkrequest.h \
    $$PWD/qml/enums/openmode.h \
    $$PWD/qml/enums/sql.h \
    $$PWD/qml/http.h \
    $$PWD/qml/httpmultipart.h \
    $$PWD/qml/httppart.h \
    $$PWD/qml/httpresponse.h \
    $$PWD/qml/mongodb.h \
    $$PWD/qml/mongofind.h \
    $$PWD/qml/mongohint.h \
    $$PWD/qml/mongoinsert.h \
    $$PWD/qml/mongoupdate.h \
    $$PWD/qml/sqldatabase.h \
    $$PWD/qml/sqlerror.h \
    $$PWD/qml/sqlquery.h \
    $$PWD/routes/bucket.h \
    $$PWD/routes/channeladdpinnedchannelmessage.h \
    $$PWD/routes/channelbulkmessagesdelete.h \
    $$PWD/routes/channelcreatechannelinvite.h \
    $$PWD/routes/channelcreatemessage.h \
    $$PWD/routes/channelcreatereaction.h \
    $$PWD/routes/channelcrosspostmessage.h \
    $$PWD/routes/channeldeleteallreactions.h \
    $$PWD/routes/channeldeleteallreactionsforemoji.h \
    $$PWD/routes/channeldeletechannel.h \
    $$PWD/routes/channeldeletechannelpermission.h \
    $$PWD/routes/channeldeletemessage.h \
    $$PWD/routes/channeldeleteownreaction.h \
    $$PWD/routes/channeldeletepinnedchannelmessage.h \
    $$PWD/routes/channeldeleteuserreaction.h \
    $$PWD/routes/channeleditchannelpermissions.h \
    $$PWD/routes/channeleditmessage.h \
    $$PWD/routes/channelfollownewschannel.h \
    $$PWD/routes/channelgetchannel.h \
    $$PWD/routes/channelgetchannelinvites.h \
    $$PWD/routes/channelgetchannelmessage.h \
    $$PWD/routes/channelgetchannelmessages.h \
    $$PWD/routes/channelgetpinnedmessages.h \
    $$PWD/routes/channelgetreactions.h \
    $$PWD/routes/channelgroupdmaddrecipient.h \
    $$PWD/routes/channelgroupdmremoverecipient.h \
    $$PWD/routes/channelmodifychannel.h \
    $$PWD/routes/channeltriggertypingindicator.h \
    $$PWD/routes/discordapi.h \
    $$PWD/routes/emojicreateguildemoji.h \
    $$PWD/routes/emojideleteguildemoji.h \
    $$PWD/routes/emojigetguildemoji.h \
    $$PWD/routes/emojilistguildemojis.h \
    $$PWD/routes/emojimodifyguildemoji.h \
    $$PWD/routes/guildaddguildmember.h \
    $$PWD/routes/guildaddguildmemberrole.h \
    $$PWD/routes/guildbeginguildprune.h \
    $$PWD/routes/guildcreateguild.h \
    $$PWD/routes/guildcreateguildban.h \
    $$PWD/routes/guildcreateguildchannel.h \
    $$PWD/routes/guildcreateguildintegration.h \
    $$PWD/routes/guildcreateguildrole.h \
    $$PWD/routes/guilddeleteguild.h \
    $$PWD/routes/guilddeleteguildintegration.h \
    $$PWD/routes/guilddeleteguildrole.h \
    $$PWD/routes/guildgetguild.h \
    $$PWD/routes/guildgetguildban.h \
    $$PWD/routes/guildgetguildbans.h \
    $$PWD/routes/guildgetguildchannels.h \
    $$PWD/routes/guildgetguildembed.h \
    $$PWD/routes/guildgetguildintegrations.h \
    $$PWD/routes/guildgetguildinvites.h \
    $$PWD/routes/guildgetguildmember.h \
    $$PWD/routes/guildgetguildpreview.h \
    $$PWD/routes/guildgetguildprunecount.h \
    $$PWD/routes/guildgetguildroles.h \
    $$PWD/routes/guildgetguildvoiceregions.h \
    $$PWD/routes/guildgetguildwidget.h \
    $$PWD/routes/guildgetguildwidgetsettings.h \
    $$PWD/routes/guildgetvanityurl.h \
    $$PWD/routes/guildgetwidgetimage.h \
    $$PWD/routes/guildlistguildmembers.h \
    $$PWD/routes/guildmodifycurrentusernick.h \
    $$PWD/routes/guildmodifyguild.h \
    $$PWD/routes/guildmodifyguildchannelposition.h \
    $$PWD/routes/guildmodifyguildembed.h \
    $$PWD/routes/guildmodifyguildintegration.h \
    $$PWD/routes/guildmodifyguildmember.h \
    $$PWD/routes/guildmodifyguildrole.h \
    $$PWD/routes/guildmodifyguildroleposition.h \
    $$PWD/routes/guildmodifyguildwidget.h \
    $$PWD/routes/guildremoveguildban.h \
    $$PWD/routes/guildremoveguildmember.h \
    $$PWD/routes/guildremoveguildmemberrole.h \
    $$PWD/routes/guildsyncguildintegration.h \
    $$PWD/routes/invitedeleteinvite.h \
    $$PWD/routes/invitegetinvite.h \
    $$PWD/routes/route.h \
    $$PWD/botjob/corecommand.h \
    $$PWD/botjob/corecommands.h \
    $$PWD/botjob/ibotjob.h \
    $$PWD/qml/file.h \
    $$PWD/qml/qmlfactory.h \
    $$PWD/routes/usercreatedm.h \
    $$PWD/routes/usergetcurrentuser.h \
    $$PWD/routes/usergetcurrentuserguilds.h \
    $$PWD/routes/usergetuser.h \
    $$PWD/routes/usergetuserconnections.h \
    $$PWD/routes/usergetuserdms.h \
    $$PWD/routes/userleaveguild.h \
    $$PWD/routes/usermodifycurrentuser.h \
    $$PWD/routes/voicelistvoiceregions.h \
    $$PWD/routes/webhookcreatewebhook.h \
    $$PWD/routes/webhookdeletewebhook.h \
    $$PWD/routes/webhookdeletewebhookwithtoken.h \
    $$PWD/routes/webhookexecutegithubcompatiblewebhook.h \
    $$PWD/routes/webhookexecuteslackcompatiblewebhook.h \
    $$PWD/routes/webhookexecutewebook.h \
    $$PWD/routes/webhookgetchannelwebhooks.h \
    $$PWD/routes/webhookgetguildwebhooks.h \
    $$PWD/routes/webhookgetwebhook.h \
    $$PWD/routes/webhookgetwebhookwithtoken.h \
    $$PWD/routes/webhookmodifywebhook.h \
    $$PWD/routes/webhookmodifywebhookwithtoken.h \
    $$PWD/util/enumutils.h \
    $$PWD/util/mimeutils.h \
    $$PWD/util/mongoutils.h \
    $$PWD/util/serializationutils.h \
    $$PWD/util/settings.h \
    $$PWD/util/globals.h \
    $$PWD/entity/guildentity.h

DISTFILES += \
    $$PWD/readme.txt \
    $$PWD/settings.ini

SOURCES += \
    $$PWD/bot.cpp \
    $$PWD/botjob/commandbinding.cpp \
    $$PWD/botjob/databasecontext.cpp \
    $$PWD/botjob/gatewaybinding.cpp \
    $$PWD/botjob/ibinding.cpp \
    $$PWD/botjob/job.cpp \
    $$PWD/botjob/jobqueue.cpp \
    $$PWD/botjob/scriptbuilder.cpp \
    $$PWD/botjob/timedbinding.cpp \
    $$PWD/botjob/timedjobs.cpp \
    $$PWD/entity/idbmanager.cpp \
    $$PWD/entity/mongoconnectionpool.cpp \
    $$PWD/entity/mongomanager.cpp \
    $$PWD/entity/sqlmanager.cpp \
    $$PWD/entitymanager.cpp \
    $$PWD/eventhandler.cpp \
    $$PWD/gateway.cpp \
    $$PWD/logging/logfactory.cpp \
    $$PWD/logging/logger.cpp \
    $$PWD/logging/logworker.cpp \
    $$PWD/payloads/activity.cpp \
    $$PWD/payloads/activityassets.cpp \
    $$PWD/payloads/activityemoji.cpp \
    $$PWD/payloads/activityparty.cpp \
    $$PWD/payloads/activitysecrets.cpp \
    $$PWD/payloads/activitytimestamps.cpp \
    $$PWD/payloads/attachment.cpp \
    $$PWD/payloads/channel.cpp \
    $$PWD/payloads/channelmention.cpp \
    $$PWD/payloads/clientstatus.cpp \
    $$PWD/payloads/embed.cpp \
    $$PWD/payloads/embedauthor.cpp \
    $$PWD/payloads/embedfield.cpp \
    $$PWD/payloads/embedfooter.cpp \
    $$PWD/payloads/embedmedia.cpp \
    $$PWD/payloads/emoji.cpp \
    $$PWD/payloads/gatewaypayload.cpp \
    $$PWD/payloads/guild.cpp \
    $$PWD/payloads/guildmember.cpp \
    $$PWD/payloads/guildroledelete.cpp \
    $$PWD/payloads/guildroleupdate.cpp \
    $$PWD/payloads/heartbeat.cpp \
    $$PWD/payloads/hello.cpp \
    $$PWD/payloads/identify.cpp \
    $$PWD/payloads/identifyproperties.cpp \
    $$PWD/payloads/invalidsession.cpp \
    $$PWD/payloads/jsonserializable.cpp \
    $$PWD/payloads/message.cpp \
    $$PWD/payloads/messageactivity.cpp \
    $$PWD/payloads/messageapplication.cpp \
    $$PWD/payloads/messagereference.cpp \
    $$PWD/payloads/permissionoverwrite.cpp \
    $$PWD/payloads/presenceupdate.cpp \
    $$PWD/payloads/ratelimit.cpp \
    $$PWD/payloads/reaction.cpp \
    $$PWD/payloads/ready.cpp \
    $$PWD/payloads/resume.cpp \
    $$PWD/payloads/role.cpp \
    $$PWD/payloads/updatestatus.cpp \
    $$PWD/payloads/user.cpp \
    $$PWD/payloads/voicestate.cpp \
    $$PWD/botjob/botscript.cpp \
    $$PWD/payloads/eventcontext.cpp \
    $$PWD/qml/http.cpp \
    $$PWD/qml/httpmultipart.cpp \
    $$PWD/qml/httppart.cpp \
    $$PWD/qml/httpresponse.cpp \
    $$PWD/qml/mongofind.cpp \
    $$PWD/qml/mongohint.cpp \
    $$PWD/qml/mongoinsert.cpp \
    $$PWD/qml/mongoupdate.cpp \
    $$PWD/qml/sqldatabase.cpp \
    $$PWD/qml/mongodb.cpp \
    $$PWD/qml/sqlerror.cpp \
    $$PWD/qml/sqlquery.cpp \
    $$PWD/routes/discordapi.cpp \
    $$PWD/botjob/corecommand.cpp \
    $$PWD/qml/file.cpp \
    $$PWD/qml/qmlfactory.cpp \
    $$PWD/routes/route.cpp \
    $$PWD/util/httputils.cpp \
    $$PWD/util/serializationutils.cpp \
    $$PWD/util/settings.cpp \
    $$PWD/entity/guildentity.cpp

