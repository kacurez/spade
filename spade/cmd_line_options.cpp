// This code was generated by CLI, a command line interface
// compiler for C++.
//

#include "cmd_line_options.hxx"

#include <map>
#include <set>
#include <string>
#include <vector>
#include <ostream>
#include <sstream>

namespace cli
{
  // unknown_option
  //
  unknown_option::
  ~unknown_option () throw ()
  {
  }

  void unknown_option::
  print (std::ostream& os) const
  {
    os << "unknown option '" << option () << "'";
  }

  const char* unknown_option::
  what () const throw ()
  {
    return "unknown option";
  }

  // unknown_argument
  //
  unknown_argument::
  ~unknown_argument () throw ()
  {
  }

  void unknown_argument::
  print (std::ostream& os) const
  {
    os << "unknown argument '" << argument () << "'";
  }

  const char* unknown_argument::
  what () const throw ()
  {
    return "unknown argument";
  }

  // missing_value
  //
  missing_value::
  ~missing_value () throw ()
  {
  }

  void missing_value::
  print (std::ostream& os) const
  {
    os << "missing value for option '" << option () << "'";
  }

  const char* missing_value::
  what () const throw ()
  {
    return "missing option value";
  }

  // invalid_value
  //
  invalid_value::
  ~invalid_value () throw ()
  {
  }

  void invalid_value::
  print (std::ostream& os) const
  {
    os << "invalid value '" << value () << "' for option '"
       << option () << "'";
  }

  const char* invalid_value::
  what () const throw ()
  {
    return "invalid option value";
  }

  template <typename X>
  struct parser
  {
    static int
    parse (X& x, char** argv, int n)
    {
      if (n > 1)
      {
        std::istringstream is (argv[1]);
        if (!(is >> x && is.eof ()))
          throw invalid_value (argv[0], argv[1]);
        return 2;
      }
      else
        throw missing_value (argv[0]);
    }
  };

  template <>
  struct parser<bool>
  {
    static int
    parse (bool& x, char**, int)
    {
      x = true;
      return 1;
    }
  };

  template <>
  struct parser<std::string>
  {
    static int
    parse (std::string& x, char** argv, int n)
    {
      if (n > 1)
      {
        x = argv[1];
        return 2;
      }
      else
        throw missing_value (argv[0]);
    }
  };

  template <typename X>
  struct parser<std::vector<X> >
  {
    static int
    parse (std::vector<X>& v, char** argv, int n)
    {
      X x;
      int i = parser<X>::parse (x, argv, n);
      v.push_back (x);
      return i;
    }
  };

  template <typename X>
  struct parser<std::set<X> >
  {
    static int
    parse (std::set<X>& s, char** argv, int n)
    {
      X x;
      int i = parser<X>::parse (x, argv, n);
      s.insert (x);
      return i;
    }
  };

  template <typename K, typename V>
  struct parser<std::map<K, V> >
  {
    static int
    parse (std::map<K, V>& m, char** argv, int n)
    {
      if (n > 1)
      {
        std::string s (argv[1]);
        std::string::size_type p = s.find ('=');

        if (p == std::string::npos)
        {
          K k = K ();

          if (!s.empty ())
          {
            std::istringstream ks (s);

            if (!(ks >> k && ks.eof ()))
              throw invalid_value (argv[0], argv[1]);
          }

          m[k] = V ();
        }
        else
        {
          K k = K ();
          V v = V ();
          std::string kstr (s, 0, p);
          std::string vstr (s, p + 1);

          if (!kstr.empty ())
          {
            std::istringstream ks (kstr);

            if (!(ks >> k && ks.eof ()))
              throw invalid_value (argv[0], argv[1]);
          }

          if (!vstr.empty ())
          {
            std::istringstream vs (vstr);

            if (!(vs >> v && vs.eof ()))
              throw invalid_value (argv[0], argv[1]);
          }

          m[k] = v;
        }

        return 2;
      }
      else
        throw missing_value (argv[0]);
    }
  };

  template <typename X, typename T, T X::*P>
  int
  thunk (X& x, char** argv, int n)
  {
    return parser<T>::parse (x.*P, argv, n);
  }
}

#include <map>
#include <cstring>

// options
//

options::
options (int argc,
         char** argv,
         ::cli::unknown_mode opt,
         ::cli::unknown_mode arg)
: support_threshold_ (),
  print_freq_seqs_ (),
  file_ (),
  help_ (),
  testing_ ()
{
  _parse (1, argc, argv, opt, arg);
}

options::
options (int start,
         int argc,
         char** argv,
         ::cli::unknown_mode opt,
         ::cli::unknown_mode arg)
: support_threshold_ (),
  print_freq_seqs_ (),
  file_ (),
  help_ (),
  testing_ ()
{
  _parse (start, argc, argv, opt, arg);
}

options::
options (int argc,
         char** argv,
         int& end,
         ::cli::unknown_mode opt,
         ::cli::unknown_mode arg)
: support_threshold_ (),
  print_freq_seqs_ (),
  file_ (),
  help_ (),
  testing_ ()
{
  end = _parse (1, argc, argv, opt, arg);
}

options::
options (int start,
         int argc,
         char** argv,
         int& end,
         ::cli::unknown_mode opt,
         ::cli::unknown_mode arg)
: support_threshold_ (),
  print_freq_seqs_ (),
  file_ (),
  help_ (),
  testing_ ()
{
  end = _parse (start, argc, argv, opt, arg);
}

typedef
std::map<std::string, int (*) (options&, char**, int)>
_cli_options_map;

static _cli_options_map _cli_options_map_;

struct _cli_options_map_init
{
  _cli_options_map_init ()
  {
    _cli_options_map_["--support-threshold"] = 
    &::cli::thunk< options, unsigned int, &options::support_threshold_ >;
    _cli_options_map_["-s"] = 
    &::cli::thunk< options, unsigned int, &options::support_threshold_ >;
    _cli_options_map_["--print-freq-seqs"] = 
    &::cli::thunk< options, bool, &options::print_freq_seqs_ >;
    _cli_options_map_["-p"] = 
    &::cli::thunk< options, bool, &options::print_freq_seqs_ >;
    _cli_options_map_["--file"] = 
    &::cli::thunk< options, std::string, &options::file_ >;
    _cli_options_map_["-f"] = 
    &::cli::thunk< options, std::string, &options::file_ >;
    _cli_options_map_["--help"] = 
    &::cli::thunk< options, bool, &options::help_ >;
    _cli_options_map_["-h"] = 
    &::cli::thunk< options, bool, &options::help_ >;
    _cli_options_map_["--testing"] = 
    &::cli::thunk< options, bool, &options::testing_ >;
    _cli_options_map_["-t"] = 
    &::cli::thunk< options, bool, &options::testing_ >;
  }
} _cli_options_map_init_;

int options::
_parse (int start,
        int argc,
        char** argv,
        ::cli::unknown_mode opt_mode,
        ::cli::unknown_mode arg_mode)
{
  bool opt = true;

  for (; start < argc;)
  {
    const char* s = argv[start];

    if (std::strcmp (s, "--") == 0)
    {
      start++;
      opt = false;
      continue;
    }

    _cli_options_map::const_iterator i (
      opt ? _cli_options_map_.find (s) : _cli_options_map_.end ());

    if (i != _cli_options_map_.end ())
    {
      start += (*(i->second)) (*this, argv + start, argc - start);
    }
    else if (opt && std::strncmp (s, "-", 1) == 0 && s[1] != '\0')
    {
      switch (opt_mode)
      {
        case ::cli::unknown_mode::skip:
        {
          start++;
          continue;
        }
        case ::cli::unknown_mode::stop:
        {
          break;
        }
        case ::cli::unknown_mode::fail:
        {
          throw ::cli::unknown_option (s);
        }
      }

      break;
    }
    else
    {
      switch (arg_mode)
      {
        case ::cli::unknown_mode::skip:
        {
          start++;
          continue;
        }
        case ::cli::unknown_mode::stop:
        {
          break;
        }
        case ::cli::unknown_mode::fail:
        {
          throw ::cli::unknown_argument (s);
        }
      }

      break;
    }
  }

  return start;
}

