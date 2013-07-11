//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_RED_BLACK_TREE_INC__
# define __GLYNOS_RED_BLACK_TREE_INC__


# include <algorithm>
# include <memory>
# include <glynos/binary_tree/node.hpp>


namespace glynos {
  template <
    class Key,
    class Value,
    class Compare
    >
  class red_black_tree {

  public:

    typedef Key key_type;
    typedef Value value_type;
    typedef binary_tree_node<Key, Value, Compare> node_type;

    red_black_tree() {

    }

    red_black_tree(const red_black_tree &other) {
      if (!other.empty()) {
	root_.reset(new node_type(*other.root_));
      }
    }

    red_black_tree(red_black_tree &&other)
      : root_(other.root_) {
      other.root_.reset();
    }

    red_black_tree &operator = (const red_black_tree &other) {
      red_black_tree(other).swap(*this);
      return *this;
    }

    red_black_tree &operator = (red_black_tree &&other) {
      red_black_tree(other).swap(std::move(*this));
      return *this;
    }

    ~red_black_tree() {

    }

    void swap(red_black_tree &other) {
      std::swap(root_, other.root_);
    }

    bool insert(const Key &key, const Value &value) {
      std::shared_ptr<const node_type> node = find(key);
      if (node) {
	return false;
      }

      std::shared_ptr<node_type> new_node(new node_type(key, value, compare_));
      if (!empty()) {
	root_->insert(new_node);
      }
      else {
	root_ = new_node;
      }

      // now sort out red/black stuff

      return true;
      // std::shared_ptr<node_type> z(new node_type(key, value, compare_));
      // std::shared_ptr<node_type> x = root_;
      // std::shared_ptr<node_type> y;
      // while (x) {
      //     y = x;
      //     if (compare_(*z->key, *x->key)) {
      //         x = x->left;
      //     }
      //     else {
      //         x = x->right;
      //     }
      // }
      // z->parent = y;
      // if (!y) {
      //     root_ = z;
      // }
      // else if (compare_(*z->key, *y->key)) {
      //     y->left = z;
      // }
      // else {
      //     y->right = z;
      // }
      // z->left.reset();
      // z->right.reset();
      // z->color = node_type::Red;
      // // insert_fixup(z);
      return true;
    }

    std::shared_ptr<node_type> find(const Key &key) {
      if (!empty()) {
	return root_->find(key);
      }
      return std::shared_ptr<node_type>();
    }

    void remove(const Key &key) {

    }

    std::shared_ptr<node_type> minimum() {
      if (!empty()) {
	return root_->minimum();
      }
      return std::shared_ptr<node_type>();
    }

    std::shared_ptr<node_type> maximum() {
      if (!empty()) {
	return root_->maximum();
      }
      return std::shared_ptr<node_type>();
    }

    template <
      class Func
      >
    void preorder_walk(const Func &func) {
      if (!empty()) {
	root_->preorder_walk(func);
      }
    }

    template <
      class Func
      >
    void inorder_walk(const Func &func) {
      if (!empty()) {
	root_->inorder_walk_2(func);
      }
    }

    template <
      class Func
      >
    void postorder_walk(const Func &func) {
      if (!empty()) {
	root_->postorder_walk(func);
      }
    }

    template <
      class Func
      >
    void levelorder_walk(const Func &func) {
      if (!empty()) {
	root_->levelorder_walk(func);
      }
    }

    template <
      class Func
      >
    void walk(const Func &func) {
      inorder_walk(func);
    }

    bool empty() const {
      return !static_cast<bool>(root_);
    }

    unsigned int count() const {
      return root_? root_->count() : 0U;
    }

    unsigned int height() const {
      return root_? root_->height() : 0U;
    }

  private:

    void left_rotate(std::shared_ptr<node_type> x) {
      std::shared_ptr<node_type> y = x->right;
      x->right = y->left;
      if (y->left) {
	y->left->parent = x;
      }
      y->parent = x->parent;
      if (!x->parent) {
	root_ = y;
      }
      else if (x == x->parent->left) {
	x->parent->left = y;
      }
      else {
	x->parent->right = y;
      }
      y->left = x;
      x->parent = y;
    }

    void right_rotate(std::shared_ptr<node_type> x) {
      std::shared_ptr<node_type> y = x->left;
      x->left = y->right;
      if (y->right) {
	y->right->parent = x;
      }
      y->parent = x->parent;
      if (!x->parent) {
	root_ = y;
      }
      else if (x == x->parent->right) {
	x->parent->right = y;
      }
      else {
	x->parent->left = y;
      }
      y->right = x;
      x->parent = y;
    }

    void insert_fixup(std::shared_ptr<node_type> z) {
      std::shared_ptr<node_type> y;
      while (z->parent->color == node_type::Red) {
	if (z->parent == z->parent->parent->left) {
	  y = z->parent->parent->right;
	  if (y->color == node_type::Red) {
	    z->parent->color = node_type::Black;
	    y->color = node_type::Black;
	    z->parent->parent->color = node_type::Red;
	    z = z->parent->parent;
	  }
	  else if (z == z->parent->right) {
	    z = z->parent;
	    left_rotate(z);
	  }
	  z->parent->color = node_type::Black;
	  z->parent->parent->color = node_type::Black;
	  right_rotate(z->parent->parent);
	}
	else {

	}
      }
    }

    std::shared_ptr<node_type> root_;
    Compare compare_;

  };
} // namespace glynos


#endif // __GLYNOS_RED_BLACK_TREE_INC__
