#include <iostream>
#include <vector>
using namespace std;
class AbstractPicture
{
protected:
    string content;

public:
    AbstractPicture(string c) : content(c) {};
    virtual string show() = 0;
};
class Picture : public AbstractPicture
{
public:
    Picture(string c) : AbstractPicture(c) {};
    string show()

    {
        return content;
    }
};
class Folder : public AbstractPicture
{
private:
    vector<AbstractPicture *> files;

public:
    Folder(string c) : AbstractPicture(c) {};
    string show()

    {
        string result = content + ':';
        for (int i = 0; i < (int)files.size(); i++)

        {
            result += (files[i]->show() + ' ');
        }
        return result;
    }
    void add(AbstractPicture *f)

    {
        files.push_back(f);
    }
    void remove(int i)

    {
        files.erase(files.begin() + i);
    }
};
class Decorator : public Picture
{
private:
    Picture *pic;

public:
    Decorator(Picture *pic) : Picture(*pic), pic(pic) {};
    string show()

    {
        return "Decorated " + pic->show();
    }
};
int main(void)
{
    Picture *p1 = new Picture("flower");
    Picture *p2 = new Picture("car");
    Picture *p3 = new Picture("watermelon");
    Picture *p4 = new Picture("dog");
    Picture *p5 = new Picture("cat");
    Picture *p6 = new Picture("apple");
    Folder *fy1 = new Folder("2023");
    Folder *fy2 = new Folder("2024");
    Folder *fm1 = new Folder("2023-10");
    Folder *fm2 = new Folder("2024-7");
    Folder *fd1 = new Folder("2023-10-7");
    Folder *fd2 = new Folder("2024-7-16");
    Folder *fd3 = new Folder("2024-7-20");
    fd1->add(new Decorator(p1));
    fd2->add(new Decorator(p2));
    fd3->add(new Decorator(p3));
    fd3->add(new Decorator(p4));
    fd3->add(new Decorator(p5));
    fd3->add(new Decorator(p6));
    fm1->add(fd1);
    fm2->add(fd2);
    fm2->add(fd3);
    fy1->add(fm1);
    fy2->add(fm2);
    cout << fy1->show() << endl;
    cout << fy2->show() << endl;
    return 0;
}
