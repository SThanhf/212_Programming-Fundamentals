/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2022
* Author: Vu Van Tien
* Date: 15.02.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

class Point
{
private:
    int x;
    int y;

public:
    Point(int, int);
    string toString() const;
    int getX() const;
    int getY() const;
    int distanceTo(const Point &otherPoint) const;
};
Point::Point(int x = 0, int y = 0)
{
    this->x = x;
    this->y = y;
}
string Point::toString() const
{
    return "<Point[" + to_string(x) + "," + to_string(y) + "]>";
}
int Point::getX() const
{
    return x;
}
int Point::getY() const
{
    return y;
}
int Point::distanceTo(const Point &otherPoint) const
{
    int x1 = x, y1 = y;
    int x2 = otherPoint.getX(), y2 = otherPoint.getY();
    return ceil(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

class Node
{
private:
    Point point;
    Node *next;

    friend class Path;

public:
    Node(const Point &point = Point(0, 0), Node *next = NULL)
    {
        this->point = point;
        this->next = next;
    };
    string toString() const;
};
string Node::toString() const
{
    return "<Node[" + (this->point).toString() + "]>";
}

class Path
{
private:
    Node *head;
    Node *tail;
    int count;
    int length;

public:
    Path();
    ~Path();

    int getLength();
    void addPoint(int x, int y);
    string toString() const;
    Point getLastPoint() const;
};
Path::Path()
{
    head = NULL;
    tail = NULL;
    count = 0;
    length = -1;
}
Path::~Path()
{
    delete head;
    delete tail;
}
void Path::addPoint(int x, int y)
{
    Node *newNode = new Node;
    *newNode = Node(Point(x, y), NULL);
    if (count == 0)
    {
        this->head = newNode;
        this->tail = newNode;
        this->count = 1;
        this->length = 0;
    }
    else
    {
        (this->tail)->next = newNode;
        this->tail = newNode;
        ++(this->count);
        this->length = 0;
        Node *temp = this->head;
        for (int i = 1; i < this->count; ++i)
        {
            Point A = temp->point;
            temp = temp->next;
            Point B = temp->point;
            this->length += B.distanceTo(A);
        }
    }
}
string Path::toString() const
{
    string result = "<Path[count:" + to_string(this->count) + ",length:" + to_string(this->length) + ",[";
    Node *temp = this->head;
    for (int i = 0; i < count; ++i)
    {
        result += temp->toString();
        if (i < count - 1)
            result += ",";
        temp = temp->next;
    }
    result += "]]>";
    return result;
}
Point Path::getLastPoint() const
{
    return (this->tail)->point;
}
int Path::getLength()
{
    return this->length;
}

class Character
{
private:
    string name;
    Path *path;

public:
    Character(const string &name = "")
    {
        this->name = name;
        this->path = new Path;
    };
    ~Character();

    string getName() const;
    void setName(const string &name);
    Path *getPath() const
    {
        return this->path;
    };
    void moveToPoint(int x, int y);
    string toString() const;
};
Character::~Character()
{
    this->path = NULL;
}
string Character::getName() const
{
    return this->name;
}
void Character::setName(const string &name)
{
    this->name = name;
}
void Character::moveToPoint(int x, int y)
{
    (this->path)->addPoint(x, y);
}
string Character::toString() const
{
    return "<Character[name:" + this->name + ",path:" + (this->path)->toString() + "]>";
}

bool rescueSherlock(
    const Character &chMurderer,
    const Character &chWatson,
    int maxLength,
    int maxDistance,
    int &outDistance)
{
    int distance = ((chWatson.getPath())->getLastPoint()).distanceTo((chMurderer.getPath()->getLastPoint()));
    int lengthW_M = (chWatson.getPath())->getLength() - (chMurderer.getPath())->getLength();
    if (lengthW_M <= maxLength)
    {
        outDistance = distance;
        if (distance <= maxDistance)
            return true;
        else
            return false;
    }
    else
    {
        outDistance = -1;
        return false;
    }
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */