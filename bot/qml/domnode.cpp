/**
 *
 *
 * Original credit to https://github.com/lagner/QGumboParser
 *
 * DOMParsing code borrows _heavily_ from here!
 */


#include <cstring>
#include <QDebug>

#include "util/serializationutils.h"
#include "domnode.h"
#include "domattribute.h"

namespace {

const char* const ID_ATTRIBUTE 		= "id";
const char* const CLASS_ATTRIBUTE 	= "class";

template<typename TFunctor>
bool iterateTree(GumboNode* node, TFunctor& functor, QObject *parent)
{
    if (!node || node->type != GUMBO_NODE_ELEMENT) {
        return false;
    }

    if (functor(node, parent)) {
        return true;
    }

    for (uint i = 0; i < node->v.element.children.length; ++i) {
        if (iterateTree(static_cast<GumboNode*>(node->v.element.children.data[i]), functor, parent)) {
            return true;
        }
    }

    return false;
}

template<typename TFunctor>
bool iterateChildren(GumboNode* node, TFunctor& functor, QObject *parent)
{
    if (node->type != GUMBO_NODE_ELEMENT) {
        return false;
    }

    GumboVector& vec = node->v.element.children;

    for (uint i = 0, e = vec.length; i < e; ++i) {
        GumboNode* node = static_cast<GumboNode*>(vec.data[i]);

        if (functor(node, parent)) {
            return true;
        }
    }

    return false;
}

} /* namespace */

DOMNode::DOMNode(const DOMNode &other, QObject *parent) : QObject(parent) {
    if(this == &other) {
        return;
    }

    _ptr = other._ptr;
}

DOMNode::DOMNode(DOMNode &&other, QObject *parent) noexcept : QObject(parent), _ptr(std::move(other._ptr)) {
}

DOMNode::DOMNode(GumboNode* node, QObject *parent) : QObject(parent), _ptr(node) {
    if (!_ptr) {
        _logger->debug("can't create Node from nullptr");
    }
}

DOMNode*
DOMNode::getElementById(const QString& nodeId) {
    Q_ASSERT(_ptr);

    DOMNode *domNode = nullptr;

    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning empty object list.");

        return domNode;
    }

    if (nodeId.isEmpty()) {
        _logger->debug("nodeId is currently null, returning empty object list.");

        return domNode;
    }

    auto functor = [&domNode, &nodeId] (GumboNode* node, QObject* parent) {
        GumboAttribute* attr = gumbo_get_attribute(&node->v.element.attributes, ID_ATTRIBUTE);

        if (attr) {
            const QString value = QString::fromUtf8(attr->value);

            if (value.compare(nodeId, Qt::CaseInsensitive) == 0) {
                domNode = new DOMNode(node, parent);

                return true;
            }
        }
        return false;
    };

    iterateTree(_ptr, functor, this);

    return domNode;
}

QList<QObject*>
DOMNode::getElementsByTagName(HtmlTag::Tag tag) {
    Q_ASSERT(_ptr);

    QList<QObject*> nodes;

    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning empty object list.");

        return nodes;
    }

    GumboTag tag_ = static_cast<GumboTag>(tag);

    auto functor = [&nodes, tag_](GumboNode* node, QObject *parent) {
        if (node->v.element.tag == tag_) {
            nodes << new DOMNode(node, parent);
        }

        return false;
    };

    iterateTree(_ptr, functor, this);

    return nodes;
}

QList<QObject*>
DOMNode::getElementsByClassName(const QString& name) {
    Q_ASSERT(_ptr);

    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning empty object list.");

        return QObjectList();
    }

    if (name.isEmpty()) {
        _logger->debug("class name can't, returning empty object list.");

        return QObjectList();
    }

    QObjectList nodes;

    auto functor = [&nodes, &name] (GumboNode* node, QObject *parent) {
        GumboAttribute* attr = gumbo_get_attribute(&node->v.element.attributes, CLASS_ATTRIBUTE);
        if (attr) {
            const QString value = QString::fromUtf8(attr->value);

            const QVector<QStringRef> parts =
                    value.splitRef(QChar(' '), Qt::SkipEmptyParts, Qt::CaseInsensitive);

            for (const QStringRef& part: parts) {
                if (part.compare(name, Qt::CaseInsensitive) == 0) {
                    nodes << new DOMNode(node, parent);

                    break;
                }
            }
        }

        return false;
    };

    iterateTree(_ptr, functor, this);

    return nodes;
}

QList<QObject*>
DOMNode::childNodes() {
    Q_ASSERT(_ptr);

    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning empty object list.");

        return QObjectList();
    }

    QObjectList nodes;

    auto functor = [&nodes] (GumboNode* node, QObject *parent) {
        nodes << new DOMNode(node, parent);

        return false;
    };

    iterateChildren(_ptr, functor, this);

    return nodes;
}

QList<QObject*>
DOMNode::children() {
    Q_ASSERT(_ptr);

    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning empty object list.");

        return QObjectList();
    }

    QObjectList nodes;

    auto functor = [&nodes] (GumboNode* node, QObject *parent) {
        if (node->type == GUMBO_NODE_ELEMENT) {
            nodes << new DOMNode(node, parent);
        }

        return false;
    };

    iterateChildren(_ptr, functor, this);

    return nodes;
}

int
DOMNode::childElementCount() {
    Q_ASSERT(_ptr);

    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning -1 child count.");

        return -1;
    }

    int count = 0;

    auto functor = [&count] (GumboNode* node, QObject *parent) {
        Q_UNUSED(parent)

        if (node->type == GUMBO_NODE_ELEMENT) {
            ++count;
        }

        return false;
    };

    iterateChildren(_ptr, functor, this);

    return count;
}

QString
DOMNode::innerText() {
    Q_ASSERT(_ptr);

    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning empty string.");

        return QString();
    }

    QString text;

    auto functor = [&text] (GumboNode* node, QObject *parent) {
        Q_UNUSED(parent)

        if (node->type == GUMBO_NODE_TEXT) {
            text += QString::fromUtf8(node->v.text.text);
        }

        return false;
    };

    iterateChildren(_ptr, functor, this);

    return text;
}

QString
DOMNode::outerHtml() const {
    Q_ASSERT(_ptr);

    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning empty string.");

        return QString();
    }

    QString text;

    switch (_ptr->type) {
    case GUMBO_NODE_DOCUMENT: {

        _logger->debug("invalid node type");

        return QString();
    }
    case GUMBO_NODE_ELEMENT: {
        const auto& elem = _ptr->v.element;

        const auto& tag = elem.original_tag;

        if (tag.data && tag.length) {
            int lenght = elem.end_pos.offset - elem.start_pos.offset + elem.original_end_tag.length;

            Q_ASSERT(lenght > 0);

            text = QString::fromUtf8(tag.data, lenght);
        }
        break;
    }
    default: {
        const auto& str = _ptr->v.text.original_text;

        text = QString::fromUtf8(str.data, str.length);
    }}
    return text;
}

QJsonObject
DOMNode::outerJson() const {
    return SerializationUtils::xmlToQJsonObject(outerHtml());
}

HtmlTag::Tag
DOMNode::tag() const {
    if (isElement()) {
        return HtmlTag::Tag(_ptr->v.element.tag);
    }

    return HtmlTag::Tag::UNKNOWN;
}

QString
DOMNode::tagName() const {
    Q_ASSERT(_ptr);

    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning empty string.");

        return QString();
    }

    GumboTag tag = _ptr->v.element.tag;

    return QString::fromUtf8(gumbo_normalized_tagname(tag));
}

QString
DOMNode::nodeName() const {
    return tagName();
}

QString
DOMNode::id() const {
    Q_ASSERT(_ptr);

    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning empty string.");

        return QString();
    }

    GumboAttribute* attr = gumbo_get_attribute(&_ptr->v.element.attributes, ID_ATTRIBUTE);

    if (attr) {
        return QString::fromUtf8(attr->value);
    }

    return QString();
}

QStringList
DOMNode::classList() const
{
    Q_ASSERT(_ptr);

    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning empty string list.");

        return QStringList();
    }

    GumboAttribute* attr = gumbo_get_attribute(&_ptr->v.element.attributes, CLASS_ATTRIBUTE);

    if (attr) {
        QString values = QString::fromUtf8(attr->value);

        return values.split(" ", Qt::SkipEmptyParts, Qt::CaseInsensitive);
    }

    return QStringList();
}

bool
DOMNode::isElement() const {
    Q_ASSERT(_ptr);

    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning false.");

        return false;
    }

    return _ptr->type == GUMBO_NODE_ELEMENT;
}

bool
DOMNode::hasAttribute(const QString& name) const
{
    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning false.");

        return false;
    }

    if (name.isEmpty()) {
        _logger->debug("Attribute name can't be empty, returning false.");

        return false;
    }

    GumboAttribute* attr = gumbo_get_attribute(&_ptr->v.element.attributes,
                                               name.toUtf8().constData());
    return attr != nullptr;
}

QString
DOMNode::getAttribute(const QString& attrName) const
{
    if (!_ptr) {
        _logger->debug("GumboNode is currently null, returning empty string.");

        return QString();
    }

    if (attrName.isEmpty()) {
        _logger->debug("attrName can't be empty, returning empty string.");

        return QString();
    }

    GumboAttribute* attr = gumbo_get_attribute(&_ptr->v.element.attributes,
                                               attrName.toUtf8().constData());
    if (attr) {
        return QString::fromUtf8(attr->value);
    }

    return QString();
}

QList<QObject*>
DOMNode::allAttributes() {
    Q_ASSERT(_ptr);

    QObjectList attrs;

    for (uint i = 0, len = _ptr->v.element.attributes.length; i < len; ++i) {
        GumboAttribute* attr =
                static_cast<GumboAttribute*>(_ptr->v.element.attributes.data[i]);

        attrs << new DOMAttribute(attr->name, attr->value, this);
    }
    return attrs;
}

DOMNode::operator bool() const {
    return _ptr;
}
