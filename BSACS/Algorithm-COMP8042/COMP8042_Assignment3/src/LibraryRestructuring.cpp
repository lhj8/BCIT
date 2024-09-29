#include "../include/LibraryRestructuring.h"


/**
 * @brief Constructor for LibraryRestructuring class.
 *
 * This constructor initializes a new LibraryRestructuring object using a collection of borrow
 * records and a collection of books. It performs several operations including populating a map
 * of all books indexed by ISBN, calculating total borrowing times for each book based on the
 * borrow records, and building a graph structure to represent relationships between books
 * based on patron borrowing patterns.
 *
 * The graph is an adjacency list representing connections between books that have been
 * borrowed by the same patron. This is used to understand the relationships and common
 * preferences among patrons.
 *
 * @param records A set of BorrowRecord instances, each containing details of individual book
 * borrowings, including the patron ID, book ISBN, checkout date, and return date.
 * @param bookCollection A set of Book instances, each containing details of a book in the
 * library, including the book's ISBN.
 */
LibraryRestructuring::LibraryRestructuring(const UnorderedSet<BorrowRecord> &records,
                                           const UnorderedSet<Book> &bookCollection) {
    for (const Book& book : bookCollection) {
        allBooks[book.ISBN] = book;
    }

    // Initialize bookBorrowingTime and build adjacency list graph
    HashTable<std::string, UnorderedSet<std::string>> patronBookTable = HashTable<std::string, UnorderedSet<std::string>>{};
    for (const BorrowRecord& record : records) {
        bookBorrowingTime[record.bookISBN] += Date::diffDuration(record.checkoutDate, record.returnDate);

        // Associate the patron with the book they borrowed
        patronBookTable[record.patronId].insert(record.bookISBN);
    }

    // Build the graph using patron-book associations
    for (const auto& pair : patronBookTable) {
        const UnorderedSet<std::string>& books = pair->value;
        for (const std::string& book1 : books) {
            for (const std::string& book2 : books) {
                if (book1 != book2) {
                    graph[book1].insert(book2);
                }
            }
        }
    }
}


/**
 * @brief Clusters and sorts books based on their borrowing patterns and other specified criteria.
 *
 * This function first clusters the books based on borrowing patterns (determined by the graph of book relationships)
 * and then sorts these clusters. The sorting of clusters is done based on the average borrowing time of the books
 * within each cluster. Inside each cluster, books are further sorted based on a specified criterion (e.g., title, author,
 * year published).
 *
 * @param sortBy A string specifying the criterion for sorting books within each cluster.
 *               Valid values are "title", "author", or "yearPublished".
 * @return A vector of vectors of strings, where each inner vector represents a cluster of book ISBNs,
 *         sorted according to the specified criterion.
 */
std::vector<std::vector<std::string>> LibraryRestructuring::clusterAndSort(const std::string &sortBy) {
    std::vector<std::vector<std::string>> clusters;
    HashTable<std::string, bool> visited;


    // Cluster the graph nodes
    for (const auto& pair : graph) {
        if (!visited[pair->key]) {
            std::vector<std::string> cluster;
            dfs(pair->key, cluster, visited);
            clusters.push_back(cluster);
        }
    }

    // Sort clusters by average borrowing time
    RadixSort<std::vector<std::string>> rSort(clusters, [this](const std::vector<std::string>& cluster) {
        return getAverageBorrowingTime(cluster);
    });
    rSort.sort();

//    MergeSort<std::vector<std::string>> sortTime([this](const std::vector<std::string>& a, const std::vector<std::string>& b) {
//        return getAverageBorrowingTime(a) < getAverageBorrowingTime(b);
//    });

    for (auto& cluster : clusters) {
        // Sort logic based on 'sortBy' (title, author, yearPublished)
        if (sortBy == "title") {
            MergeSort<std::string> titleSort([this](const std::string& book1, const std::string& book2) {
                return allBooks[book1].title < allBooks[book2].title;
            });
            titleSort.sort(cluster);
        }
        if (sortBy == "author") {
            MergeSort<std::string> authorSort([this](const std::string& book1, const std::string& book2) {
                return allBooks[book1].author < allBooks[book2].author;
            });
            authorSort.sort(cluster);
        }
        if (sortBy == "yearPublished") {
            MergeSort<std::string> yearPublishedSort([this](const std::string& book1, const std::string& book2) {
                return allBooks[book1].yearPublished < allBooks[book2].yearPublished;
            });
            yearPublishedSort.sort(cluster);
        }
    }

    return clusters;
}


/**
 * @brief Performs a depth-first search (DFS) on the book relationship graph.
 *
 * This method is used to traverse the graph representing book relationships in the library.
 * It is part of the clustering process, where books that are closely related (based on borrowing patterns)
 * are grouped together. The method recursively visits each book (node in the graph) that hasn't been visited
 * yet, marking them as visited and adding them to the current cluster.
 *
 * @param current The current book ISBN being visited in the graph.
 * @param cluster A reference to a vector of strings, representing the current cluster of related books.
 *                As the DFS progresses, books are added to this cluster.
 * @param visited A hash table keeping track of whether a book (node) has been visited in the DFS.
 *                It is keyed by book ISBN with a boolean value indicating visited status.
 */
void LibraryRestructuring::dfs(const std::string &current, std::vector<std::string> &cluster,
                               HashTable<std::string, bool> &visited) {
    visited[current] = true;
    cluster.push_back(current);

    for (const auto& neighbor : graph[current]) {
        if (!visited[neighbor]) {
            dfs(neighbor, cluster, visited);
        }
    }
}


/**
 * @brief Calculates the average borrowing time for a cluster of books.
 *
 * This method computes the average borrowing time for a given cluster of books. It iterates
 * through each book in the cluster, summing up their individual borrowing times, and then
 * divides the total by the number of books in the cluster. The average borrowing time is a
 * measure of how long, on average, each book in the cluster has been borrowed.
 *
 * @param cluster A vector of strings, where each string represents the ISBN of a book in the cluster.
 * @return The average borrowing time as a double. If the cluster is empty, the method returns 0.0.
 */
 double LibraryRestructuring::getAverageBorrowingTime(const std::vector<std::string> &cluster) {
    double totalBorrowingTime = 0.0;

    if (cluster.empty()) {
        return 0.0;
    }

    for (const std::string& bookISBN : cluster) {
        totalBorrowingTime += bookBorrowingTime[bookISBN];
    }

    return totalBorrowingTime / (double)cluster.size();
}
