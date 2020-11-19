TEMPLATE = aux

INSTALLER = installer

INPUT = $$PWD/config/config.xml $$PWD/packages
bot.input = INPUT
bot.output = $$INSTALLER
bot.commands = binarycreator -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
bot.CONFIG += target_predeps no_link combine

QMAKE_EXTRA_COMPILERS += bot
