/*This program tracks the company to which a student
is employed. If companies "merge" and become a joint
company, the program will keep track of this and report
that students previously in their solitary company now
belong to the new joint company. Similarly, if "split"
is called, it will split the parent company that two
groups of subcompanies belong to, making these subcompanies
solitary again.

This program also utilizes code from the "company.hpp" file*/
#include "company.hpp"
#include <iostream>

using namespace std;

CompanyTracker::CompanyTracker (int n)
  // initializes the tracker with n students and their 1-person companies
{
  numCompanies = n;
  companies = new Company* [numCompanies];
  for (int i = 0; i < numCompanies; ++i)
      companies[i] = new Company ();
}

CompanyTracker::~CompanyTracker ()
  // deallocates all dynamically allocated memory
{
  //looping through companies and splitting them,
  //as splitting deallocates
  for(int i = 0; i < numCompanies ; i++)
  {
    while(supremeCompany(i) != companies[i]){
      split(i);
    }
  }

  for(int i = 0; i < numCompanies; i++)
  {
    delete companies[i];
  }

  delete companies;


}

Company* CompanyTracker::supremeCompany (int i)
  /*takes in company i and travels up its parent
  pointers to find its ultimate parent company*/
{
  //check for out of bounds?
  Company* supreme = companies[i];
  //something here prompting error
  while(supreme->parent != nullptr)
  {
    supreme = supreme->parent;
  }
  return supreme;
}

void CompanyTracker::merge (int i, int j)
  /* Merges the largest companies containing students i and j,
     according to the rules described above.
     That is, it generates a new Company object which will
     become the parent company of the largest companies currently
     containing students i and j.
     If i and j already belong to the same company (or are the same),
     merge doesn't do anything.
     If either i or j are out of range, merge doesn't do anything. */
{
  if((companies[i] == companies[j]) || (supremeCompany(i) == supremeCompany(j)) ||
      i < 0 || j < 0 || i >= numCompanies || j >= numCompanies)
  {
    return;
  }

  Company* ij = new Company (supremeCompany(i),supremeCompany(j));
  supremeCompany(i)->parent = ij;
  supremeCompany(j)->parent = ij;
}

void CompanyTracker::split (int i)
  /* Splits the largest company that student i belongs to,
     according to the rules described above.
     That is, it deletes that Company object, and makes sure that
     the two subcompanies have no parent afterwards.
     If i's largest company is a 1-person company, split doesn't do anything.
     If i is out of range, split doesn't do anything. */
{
  //end function if i is one person company or out of range
  Company* temp = supremeCompany(i);

  if(temp == companies[i] || i < 0 || i >= numCompanies)
  {
    return;
  }

  for(int k = 0; k < numCompanies; k++)
  {
    if(companies[k]->parent == temp)
    {
      companies[k]->parent = nullptr;
    }
  }

  temp->merge1->parent = nullptr;
  temp->merge2->parent = nullptr;
  temp->merge1 = nullptr;
  temp->merge2 = nullptr;
  delete temp;
}

bool CompanyTracker::inSameCompany (int i, int j)
  /* Returns whether students i and j are currently in the same company.
     Returns true if i==j.
     Returns false if i or j (or both) is out of range. */
{
  //checking for out of range
  if(i < 0 || j < 0 || i >= numCompanies || j >= numCompanies)
  {
    return false;
  }

  //returns true if i and j are equal or share a parent company
  if((i == j) || (supremeCompany(i) == supremeCompany(j)))
  {
    return true;
  }

  //final return statement to account for compiler warning
  return false;
}
