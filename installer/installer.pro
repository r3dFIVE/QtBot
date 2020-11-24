TEMPLATE = aux

VERSION = 0.9.9

INSTALLER = "QtBot-Installer-$$VERSION"

INPUT = $$PWD/config/config.xml $$PWD/packages
bot.input = INPUT
bot.output = $$INSTALLER
bot.commands = binarycreator -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
bot.CONFIG += target_predeps no_link combine

QMAKE_EXTRA_COMPILERS += bot


DISTFILES += \
    packages/QtBot.Scripts.Script1/data/scripts/.gitignore \
    packages/QtBot.Scripts.Script1/meta/package.xml \
    packages/QtBot.Scripts.Script2/data/scripts/.gitignore \
    packages/QtBot.Scripts.Script2/meta/package.xml \
    packages/QtBot.Scripts.Script3/data/scripts/.gitignore \
    packages/QtBot.Scripts.Script3/meta/package.xml \
    packages/QtBot.Scripts/meta/package.xml \
    packages/QtBot/data/.gitignore \
    packages/QtBot/meta/installscript.qs \
    packages/QtBot/meta/package.xml \
    packages/QtBot/meta/license.txt

