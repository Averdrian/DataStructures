#include <type_traits>
#include <vector>

template <typename T>
struct IsOrderable {
private:
    template <typename U>
    static auto test(int) -> decltype(std::declval<U>() < std::declval<U>(), std::true_type{});

    template <typename U>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T>
class SearchTree {

    public:
        static_assert(IsOrderable<T>::value, "SearchTree's type must be orderable");

    private:

        T value;
        SearchTree<T> *left, *right;

    public:

        SearchTree() : value(T()), left(nullptr), right(nullptr) {}

        SearchTree(const T &val) : value(val), left(nullptr), right(nullptr) {}

        ~SearchTree() {
            delete this->left;
            delete this->right;
        }

        T root() {
           return this->value; 
        }

        bool insert(const T &val) {

            //This SearchTree has no repetition of values,
            // if the value is already in the tree, it just do nothing and returns false
            if(this->value == T()) this->value = val;

            else if(val == this->value) return false;

            else if(val < this->value) {
                if(this->left == nullptr) {
                    this->left = new SearchTree<T>(val);
                }
                else return left->insert(val);
            }

            else {
                if(this->right == nullptr) { 
                    this->right = new SearchTree<T>(val);
                }
                else return right->insert(val);
            }

            return true;

        }

        bool remove(const T &val) {
            //TODO
            return false;
        }

        //Returns all the ordered values in a vector
        std::vector<T> toVector() {

            std::vector<T> leftV = {};
            std::vector<T> rightV = {};

            if(this->left != nullptr) leftV = this->left->toVector();
            leftV.push_back(this->value);
            if(this->right != nullptr) rightV = this->right->toVector();

            std::vector<T> full;
            full.reserve(leftV.size() + rightV.size());
            full.insert( full.end(), leftV.begin(), leftV.end() );
            full.insert( full.end(), rightV.begin(), rightV.end() );

            return full;
        }

        bool isEmpty() {
            return this->left == nullptr && this->right == nullptr && this->value == T();
        }

        bool isLeaf() {
            return this->left == nullptr && this->right == nullptr && this->value != T();
        }




};