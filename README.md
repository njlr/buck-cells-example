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

## Notes

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
