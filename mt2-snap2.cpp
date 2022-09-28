// S014646 - ABDULLAH SAYDEMİR
// GCC (Ubuntu 11.1.0-1ubuntu1~20.04) 11.1.0

// ---- READ CAREFULLY ----
// During the exam, you MUST upload your code's snapshots at 16:30, 17:30, and finally 18:30 or before the exam ends.
// ALWAYS CHECK YOUR UPLOADED CODE BY DOWNLOADING IT BACK FROM THE LMS.
// IN CASE OF A PROBLEM, EMAIL YOUR SNAPSHOT TO THE INSTRUCTOR AND ALL TEACHING ASSISTANTS.

// A snapshot is the *.cpp file of your solution at a specific time.
// 1st snapshot is at 16:30 (16:20-16:40 range is fine):
// Snapshot itself will be graded as 10 points if everything compiles, 5 points if not.
// Not submitting a snapshot costs you (minus) -25 points.
// 2nd snapshot is at 17:30 (17:20-17:40 range is fine):
// This snapshot must show at least a tiny improvement on Snapshot 1.
// Otherwise it will be considered as not uploaded.
// Snapshot itself will be graded as 10 points if everything compiles, 5 points if not.
// Not submitting or submitting the same snapshot as 1st one costs you (minus) -25 points.
// 3rd snapshot is the completed exam. This code must definitely compile for us to grade it!
// This snapshot will not be given grades itself. This snapshot can be the same with the 2nd snapshot, no problem.
// For extra exam rules, please look at the "main" function below.
// ---- READ CAREFULLY ----

#include <iostream>
#include <vector>
#include <list>
#include <array>

using namespace std;

template<typename T>
concept IsContainer = requires(T t) {
    t.begin();
    t.end();
    t.size();
};

auto accumulate_(const IsContainer auto& container, auto initval, auto lambda)
{
    auto a = initval;
    for(const auto& item : container)
        a = lambda(a, item);
    return a;
}

template<typename Container>
requires(IsContainer<Container>)
auto filter_(const Container& container, auto lambda)
{
    auto new_container = Container{};
    for(const auto& item : container)
        if(lambda(item))
            new_container.push_back(item);
    return new_container;
}

// YOU CAN WRITE YOUR CODE HERE - BEGIN 1

template<typename T> concept IsString = requires(T t) { t.c_str(); };
template <typename T> concept ConNotStr = IsContainer<T> && !IsString<T>;

template <typename T>
struct TD;

auto print_(const auto& item)
{
    cout << item << endl;
}

template <template <typename ...> typename T, typename U>
auto print_(const T<U>& container)
requires(!IsString<T<U>> && IsContainer<T<U>>)
{
    cout << "level 0: current item is a container with " << container.size() << " items which are:" << endl;
    if constexpr( !IsString<U> )
    {
        for (const auto& inner_container : container)
        {
            cout << " level 1: current item is a container with " << inner_container.size() << " items which are:" << endl;
            for(const auto& item : inner_container)
            {
                cout << " ";
                print_(item);
            }
            cout << endl;
        }
    }
    else
        for (const auto& item : container)
            print_(item);

    cout << endl;
}

auto print_(const auto& ... ts)
{
    auto a = 0;
    ((cout << "Printing item " << ++a << endl, print_(ts)), ...);
}


// YOU CAN WRITE YOUR CODE HERE - END 1

int main(int, char* [])
{
    // accumulate_ and filter_ free-functions, and IsContainer concept are already given to you.

    // Q1: Accumulate an array of any number of strings in a single string by concatenating all of them.
    // Q1a (5pts): Write initval1 correctly to match with the console output given.
    // Q1b (5pts): Write lambda1 correctly to match with the console output given.

    // Q2: Accumulate a vector of strings in such a way that strings are clustered according to their length.
    // This means that strings with a lendth of L will be accumulated in Lth container in the returned container of containers.
    // Check the console output for more informative understanding.
    // Hint: std::vector has a resize(int) method that dynamically allocates different number of item slots at run-time.
    // Q2a (5pts): Write initval2 correctly.
    // Q2b (20pts): Write lambda2 correctly.

    // Q3: Filter the container such that only the clusters of strings that are non-empty stays.
    // Q3a (5pts): Write lambda_filter correctly.

    // Q4: Write a print_ overload-set that matches the supplied console output.
    // Q4a (10pts) print_(result_filtered[0]); matches with the console output given.
    // Q4b (5pts) print_(result_filtered[0][0]); matches with the console output given.
    // Q4c (15pts) print_(result_filtered); matches with the console output given. Be careful about the indentations depending on the level.
    // Q4d (10pts) print_(result_filtered[0], result_filtered[0][0], result_filtered); matches with the console output given.
    //      In this question, variable input version of print_ free-function writes "Printing item 1", "Printing item 2", ...
    //      kind of extra lines when compared with the above print_ that prints single thing at a time. Do not miss that.
    // Hint: Be careful, std::string is also a container! std::string is implemented as a container of "char"s in std library.
    //       So, IsContainer concept returns true for std::string type as well.
    // Q5 (10pts): Snapshot 1
    // Q6 (10pts): Snapshot 2

    // YOU CAN WRITE YOUR CODE HERE - BEGIN 2
    auto initval1 = string("START");
    auto lambda1 = [](const auto& str1, const auto& str2) { return str1 + "_" +str2; };

    auto initval2 = vector<vector<string>>();

    auto lambda2 = [](auto& container, const auto& item)
    {
        auto index = container.size();

        if(item.size() >= index)
            container.resize(item.size()+1);

        container[item.size()].push_back(item);

        return container;
    };

    auto lambda_filter = [](const auto& item) { return !(item.size() == 0); };

    // YOU CAN WRITE YOUR CODE HERE - END 2

    {
        auto container = array<string, 10>{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        auto result = accumulate_(container, initval1, lambda1);

        cout << "Printing concatenation of all strings in the container:" << endl;
        print_(result);
        cout << endl;
    }

    {
        auto container = vector<string>{"quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};

        auto result = accumulate_(container, initval2, lambda2);

        cout << "Grouped the strings according to their length. Size of the result container is " << result.size() << endl;
        for(int i=0; i<result.size(); ++i)
            cout << result[i].size() << " strings with length " << i << endl;

        auto result_filtered = filter_(result, lambda_filter);
        cout << "Size of result_filtered container that contains only non-empty strings is " << result_filtered.size() << endl;
        for(int i=0; i<result_filtered.size(); ++i)
            cout << result_filtered[i].size() << " strings with length " << result_filtered[i][0].size() << endl;

        cout << "Printing index 0 of the container, which is another container by the way" << endl;
        print_(result_filtered[0]);

        cout << "Printing the first element of the container in result_filtered[0]" << endl;
        print_(result_filtered[0][0]);

        cout << "Printing the whole container" << endl;
        print_(result_filtered);

        cout << "This time, printing all the above in one shot:" << endl;
        print_(result_filtered[0], result_filtered[0][0], result_filtered);
    }

    return 0;
}
