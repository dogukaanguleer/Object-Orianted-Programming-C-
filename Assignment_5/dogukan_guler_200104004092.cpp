#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// ======================================BOOK============================================
class Book
{
public:
  /*==============================GET SET INLINE FUNCTIONS OF BOOK============================*/
  /*sets the each field(title, author, year, tag) ,takes a vector and sets vectors element to fields.*/
  void set_entities(vector<string> v)
  {
    int i;
    vector<string>::iterator itr = v.begin(); /*creates a iterator */

    for (i = 0; itr != v.end(); itr++, i++)
      entities[i] = *itr;

    field_number = i;
  }
  string get_data()
  {
    stringstream ss;
    for (int i = 0; i < field_number; i++)
    {
      ss << "\"" << entities[i] << "\"";
      if (i + 1 != field_number)
        ss << " ";
    }
    ss << endl;
    string s = ss.str();
    return s;
  }
  string get_title() { return entities[0]; }
  int get_field_number() { return field_number; }
  string get_one_entity(int index) { return entities[index]; }
  vector<string> get_fields() { return vect; }

  void sort_each(vector<Book> objects, int i, ofstream &f)
  {
    if (i == 0)
      sort(objects.begin(), objects.end(), [](const Book &lhs, const Book &rhs)
           { return lhs.entities[0] < rhs.entities[0]; });
    if (i == 1)
      sort(objects.begin(), objects.end(), [](const Book &lhs, const Book &rhs)
           { return lhs.entities[1] < rhs.entities[1]; });
    if (i == 2)
      sort(objects.begin(), objects.end(), [](const Book &lhs, const Book &rhs)
           { return lhs.entities[2] < rhs.entities[2]; });
    if (i == 3)
      sort(objects.begin(), objects.end(), [](const Book &lhs, const Book &rhs)
           { return lhs.entities[3] < rhs.entities[3]; });
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
      f << it->get_data();
    }
  }

private:
  string entities[4];
  int field_number;
  vector<string> vect{"\"title\"", "\"authors\"", "\"year\"", "\"tags\""};
};

//=========================================MUSIC============================================
class Music
{
public:
  /*==============================GET SET INLINE FUNCTIONS OF MUSIC============================*/

  /*sets the each field(title, artists, year, genre),  takes a vector and sets vectors element to fields.*/
  void set_entities(vector<string> v)
  {
    int count = 0, i;
    vector<string>::iterator itr = v.begin();
    for (i = 0; itr != v.end(); itr++, i++)
      entities[i] = *itr;
    field_number = i;
  }

  string get_data()
  {
    stringstream ss;
    for (int i = 0; i < field_number; i++)
    {
      ss << "\"" << entities[i] << "\"";
      if (i + 1 != field_number)
        ss << " ";
    }
    ss << endl;
    string s = ss.str();
    return s;
  }
  /*======================get set functions==================*/
  string get_title() { return entities[0]; }
  int get_field_number() { return field_number; }
  string get_one_entity(int index) { return entities[index]; }
  vector<string> get_fields() { return vect; }

  /* sorts according the selected area  */
  void sort_each(vector<Music> objects, int i, ofstream &f)
  {
    if (i == 0)
      sort(objects.begin(), objects.end(), [](const Music &lhs, const Music &rhs)
           { return lhs.entities[0] < rhs.entities[0]; });
    if (i == 1)
      sort(objects.begin(), objects.end(), [](const Music &lhs, const Music &rhs)
           { return lhs.entities[1] < rhs.entities[1]; });
    if (i == 2)
      sort(objects.begin(), objects.end(), [](const Music &lhs, const Music &rhs)
           { return lhs.entities[2] < rhs.entities[2]; });
    if (i == 3)
      sort(objects.begin(), objects.end(), [](const Music &lhs, const Music &rhs)
           { return lhs.entities[3] < rhs.entities[3]; });
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
      f << it->get_data();
    }
  }

private:
  string entities[4];
  int field_number;
  vector<string> vect{"\"title\"", "\"artists\"", "\"year\"", "\"genre\""};
};

//============================================MOVIE=============================================
class Movie
{
public:
  /*==============================GET SET INLINE FUNCTIONS OF MOVIE===================================*/

  void set_entities(vector<string> v) /*  sets the each field(title, director, year, genre,starring),  takes a vector and sets vectors element to fields.*/
  {
    int count = 0, i;
    vector<string>::iterator itr = v.begin();
    for (i = 0; itr != v.end(); itr++, i++)
    {
      entities[i] = *itr;
    }
    field_number = i;
  }
  int get_field_number() { return field_number; }
  string get_title() { return entities[0]; }
  string get_one_entity(int index) { return entities[index]; }
  vector<string> get_fields() { return vect; }

  string get_data()
  {
    stringstream ss;
    for (int i = 0; i < field_number; i++)
    {
      ss << "\"" << entities[i] << "\"";
      if (i + 1 != field_number)
        ss << " ";
    }
    ss << endl;
    string s = ss.str();
    return s;
  }

  /* sorts according the selected area  */
  void sort_each(vector<Movie> objects, int i, ofstream &f)
  {
    if (i == 0)
      sort(objects.begin(), objects.end(), [](const Movie &lhs, const Movie &rhs)
           { return lhs.entities[0] < rhs.entities[0]; });
    if (i == 1)
      sort(objects.begin(), objects.end(), [](const Movie &lhs, const Movie &rhs)
           { return lhs.entities[1] < rhs.entities[1]; });
    if (i == 2)
      sort(objects.begin(), objects.end(), [](const Movie &lhs, const Movie &rhs)
           { return lhs.entities[2] < rhs.entities[2]; });
    if (i == 3)
      sort(objects.begin(), objects.end(), [](const Movie &lhs, const Movie &rhs)
           { return lhs.entities[3] < rhs.entities[3]; });
    if (i == 4)
      sort(objects.begin(), objects.end(), [](const Movie &lhs, const Movie &rhs)
           { return lhs.entities[4] < rhs.entities[4]; });
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
      f << it->get_data();
    }
  }

private:
  string entities[5];
  int field_number;
  vector<string> vect{"\"title\"", "\"director\"", "\"year\"", "\"genre\"", "\"starring\""};
};

//========================================TEMPLATE CATALOG=======================================
template <class T>
class Catalog
{

public:
  void set_data(T obj) { objects.push_back(obj); }
  string get_entries()
  {
    stringstream ss;
    ss << objects.size() << " unique entries" << endl;
    string s = ss.str();
    return s;
  }
  string get_title(int index) { return objects[index].get_title(); }
  vector<string> get_field() { return objects[0].get_fields(); }

  bool duplicate_check(string str)
  {
    static int duplicate_count = 0;

    for (int i = 0; i < objects.size(); i++)
    {
      if (objects[i].get_title() == str)
      {
        return false;
      }
    }
    return true;
  }
  /*search according given index. First parse the given quote word. */
  void search(string str, int index, ofstream &f)
  {

    string delimiter = "\"", clean_string;
    size_t pos = 0;
    string token;
    int count = 0;
    while ((pos = str.find(delimiter)) != string::npos)
    {
      token = str.substr(0, pos);
      if (count == 1)
        clean_string = token;
      str.erase(0, pos + delimiter.length());
      count++;
    }

    for (int i = 0; i < objects.size(); i++)
    {
      if (objects[i].get_one_entity(index).find(clean_string) != string::npos)
      {
        f << objects[i].get_data();
      }
    }
  }

  void sort_objects(int type, ofstream &f)
  {
    T m;
    m.sort_each(objects, type, f);
  }

private:
  vector<T> objects;
};

//====================TEMPLATE PARSE LİNE FUNCTION=========================================
//Parse lines and assing fields to a temp vector and return title name to duplicate control.
template <class T>
string parse_lines(T obj, string str)
{
  ifstream data_file("data.txt");
  int count = 0;
  string delimiter = "\""; /*parse delimiter*/
  size_t pos = 0;
  string token;
  vector<string> temp; /*create a temp vector to pass object */

  while ((pos = str.find(delimiter)) != string::npos)
  {
    token = str.substr(0, pos);

    if (count % 2 != 0) /*push data to temp vector, if the token count is odd. ( 0 "1" 2 "3" ) */
    {
      temp.push_back(token);
    }
    str.erase(0, pos + delimiter.length());
    count++;
  }
  obj->set_entities(temp);

  return temp[0]; /*return title to duplicate check.*/
}

/*Search and sort */
template <class T>
void search_sort(Catalog<T> catalog, ofstream &f)
{

  ifstream command_file("commands.txt");
  string str;
  //ofstream out_file("output.txt");

  while (getline(command_file, str)) /*checks the all file*/
  {
    stringstream s(str); // Used for breaking words
    string word;
    s >> word;
    bool controlFlag = true;
    vector<string> v1 = catalog.get_field(); // gets the fields name each catalog has different field names.

    if (word == "search") /*if command is search*/
    {
      string str1;
      s >> str1;
      s >> word;
      if (word == "in")
      {
        s >> word;
        for (int i = 0; i < v1.size(); i++) /*for field times.*/
        {
          if (word == v1[i]) /*checks the fields by one by*/
          {
            f << str << endl;
            catalog.search(str1, i, f); /* i tells which field it is. Example, 0=title, 1 =author, etc.*/
            controlFlag = false;
          }
        }
        if (controlFlag == true) /*if given field is non of the catalog fields. Give an exception*/
        {
          f << "Exception: command is wrong" << endl;
          f << str << endl;
        }
      }
    }
    else if (word == "sort") /*if command is sort*/
    {
      s >> word;
      for (int i = 0; i < v1.size(); i++) /*for field times.*/
      {
        if (word == v1[i]) /*checks the fields by one by*/
        {
          f << str << endl;
          catalog.sort_objects(i, f); /* i tells which field it is. Example, 0=title, 1 =author, etc.*/
          controlFlag = false;
        }
      }
      if (controlFlag == true) /*if given field is non of the catalog fields. Give an exception*/
      {
        f << "Exception: command is wrong" << endl;
        f << str << endl;
      }
    }
  }
}

//================================MAIN FUNCTION==============================================
int main()
{
  ifstream data_file("data.txt"), command_file("commands.txt");
  ofstream out_f("output.txt");
  string str;

  data_file >> str;

  if (str == "book") /*if data.txt a has book catalog*/
  {
    out_f << "Catalog Read: book" << endl;
    Catalog<Book> catalog;
    Book *m = new Book; /*create new Book object*/
    getline(data_file, str);
    while (getline(data_file, str))
    {
      if (catalog.duplicate_check(parse_lines(m, str))) /*check duplicate of catalog.*/
      {
        if (4 != m->get_field_number()) /*check missing fields*/
        {
          out_f << "Exception: missing field" << endl;
          out_f<<m->get_data();
        }
        else
        {
          catalog.set_data(*m); /*if object is valid, then adds the catalog using set function */
        }
      }
      else
      {
        if (4 != m->get_field_number())
          out_f << "Exception: missing field" << endl;
        else
          out_f << "Exception: duplicate entry" << endl;
        out_f<<m->get_data(); /*prints invalid data*/
      }
    }
    out_f << catalog.get_entries(); /*prints the number of unique entries*/
    search_sort(catalog, out_f);    /*call the function to process search and sort operations. */
  }
  else if (str == "music") /*if data.txt a has music catalog*/
  {
    out_f << "Catalog Read: music" << endl;
    Catalog<Music> catalog;
    Music *m = new Music; /*create new Music object*/

    getline(data_file, str);
    while (getline(data_file, str))
    {
      if (catalog.duplicate_check(parse_lines(m, str)))
      {
        if (4 != m->get_field_number()) /*check missing fields*/
        {
          out_f << "Exception: missing field" << endl;
          out_f<<m->get_data(); /*prints invalid data*/
        }
        else
        {
          catalog.set_data(*m); /*if object is valid, then adds the catalog using set function */
        }
      }
      else
      {
        if (4 != m->get_field_number())
          out_f << "Exception: missing field" << endl;
        else
          out_f << "Exception: duplicate entry" << endl;
        out_f<<m->get_data(); /*prints invalid data*/
      }
    }
    out_f << catalog.get_entries(); /*prints the number of unique entries*/
    search_sort(catalog, out_f);    /*call the function to process search and sort operations. */
  }
  else if (str == "movie") /*if data.txt a has movie catalog*/
  {
    out_f << "Catalog Read: movie" << endl;
    Catalog<Movie> catalog;
    Movie *m = new Movie; /*create new Movie object*/

    getline(data_file, str);
    while (getline(data_file, str))
    {
      if (catalog.duplicate_check(parse_lines(m, str)))
      {
        if (5 != m->get_field_number()) /*check missing fields*/
        {
          out_f << "Exception: missing field" << endl;
          out_f<< m->get_data();
        }
        else
        {
          catalog.set_data(*m); /*if object is valid, then adds the catalog using set function */
        }
      }
      else
      {
        if (5 != m->get_field_number())
          out_f << "Exception: missing field" << endl;
        else
          out_f << "Exception: duplicate entry" << endl;
        out_f<< m->get_data(); /*prints invalid data*/
       
      }
    }
    out_f << catalog.get_entries(); /*prints the number of unique entries*/
    search_sort(catalog, out_f);    /*call the function to process search and sort operations. */
    out_f.close();
  }
  else
  {
    return 0;
  }
}
