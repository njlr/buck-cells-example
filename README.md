# buck-cells-example

This is an example of how [Buck](https://www.buckbuild.com) can be used with Git Submodules, rather than as a mono-repo build-system.

For this example, we are using [LoopPerfect/neither](https://github.com/LoopPerfect/neither), an `Either` implementation in C++ 14. The library is in a submodule at `vendor/neither`.

## Build Instructions

First grab the submodules using:

```bash=
git submodule update --init --recursive
```

Next, build the example with [Buck](https://www.buckbuild.com):

```bash=
buck run :example
```

## What Problem Does Cells Solve? 

Cells are a great fit for this situtation: 

 - You have a library in a repo that builds with Buck
 - You want to use that library in your project
 - You you copy the library into your project but the library's `BUCK` files don't work, because the root (`//`) has changed to the root of your project
 - You don't want to rewrite your library's `BUCK` files

Cells allow us to create isolated sub-projects that have their own `.buckconfig` and their own Buck target heirarchy. Cells can use targets from other cells when those targets are exported. 

## How Does it Work?

The meat of the example is in `.buckconfig`:

```ini=
[repositories]
  neither = vendor/neither
```

The `repositories` tag tells Buck where each cell lives in your project's folder structure. Each cell has an alias. Here we have `neither = vendor/neither`, which means `vendor/neither` has the cell-name `neither`.

We can refer to targets inside of a cell using this syntax: `cell-name//:target-in-cell`.

So to make our `example` target depend on LoopPerfect/neither:

```python=
deps = [
  'neither//:neither',
],
```

This is a really powerful feature, because it makes a library's `BUCK` files portable. All you need to do to expose a target inside of a cell is to make it public:

```python=
visibility = [
  'PUBLIC',
]
```

If you have a complex dependency graph, or if you just want something more convenient, you should consider using [Buckaroo](https://www.buckaroo.pm). Buckaroo will flatten your dependency graph, fetch source-code and write the appropriate `repositories` tags.
