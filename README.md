# GitHub User Activity Viewer

A simple C++ console app that shows the latest public activity of a GitHub user using the GitHub API.

## Features

- Fetches recent events from a GitHub user
- Shows actions like:
  - ⭐ Starred a repository  
  - 🛠️ Pushed commits  
  - 🐞 Opened issues  
- Input GitHub username from the terminal
- Uses `libcurl` to make HTTP requests
- Uses `Boost.PropertyTree` to read JSON

## Requirements

- C++17 or later
- [libcurl](https://curl.se/libcurl/)
- [Boost.PropertyTree](https://www.boost.org/doc/libs/release/doc/html/property_tree.html)
- [vcpkg](https://github.com/microsoft/vcpkg) (to install libraries easily)

## How to Build (with vcpkg)

1. Clone vcpkg and integrate it:
   ```bash
   git clone https://github.com/microsoft/vcpkg
   .\vcpkg\bootstrap-vcpkg.bat

[project URL](https://roadmap.sh/projects/github-user-activity)
