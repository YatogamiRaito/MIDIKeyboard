# Contributing to Arduino MIDI Keyboard

Thank you for your interest in contributing! This document provides guidelines and instructions for contributing to the Arduino MIDI Keyboard project.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [How to Contribute](#how-to-contribute)
- [Development Guidelines](#development-guidelines)
- [Submitting Changes](#submitting-changes)
- [Reporting Bugs](#reporting-bugs)
- [Suggesting Features](#suggesting-features)

## Code of Conduct

### Our Pledge

We are committed to providing a welcoming and inclusive environment for all contributors, regardless of experience level, background, or identity.

### Expected Behavior

- Be respectful and constructive in all interactions
- Welcome newcomers and help them get started
- Accept constructive criticism gracefully
- Focus on what's best for the project and community

### Unacceptable Behavior

- Harassment, discrimination, or offensive comments
- Personal attacks or trolling
- Spam or off-topic discussions
- Publishing others' private information

## Getting Started

### Prerequisites

Before contributing, make sure you have:

1. **Arduino IDE** (1.8.13 or newer)
2. **MIDIUSB library** installed
3. **Arduino Leonardo/Micro** or compatible board
4. **Git** installed on your computer
5. **GitHub account**

### Setting Up Development Environment

1. **Fork the repository** on GitHub
2. **Clone your fork** locally:
   ```bash
   git clone https://github.com/YOUR-USERNAME/MIDIKeyboard.git
   cd MIDIKeyboard
   ```
3. **Add upstream remote**:
   ```bash
   git remote add upstream https://github.com/YatogamiRaito/MIDIKeyboard.git
   ```
4. **Create a branch** for your changes:
   ```bash
   git checkout -b feature/your-feature-name
   ```

## How to Contribute

### Types of Contributions

We welcome various types of contributions:

#### Code Contributions
- Bug fixes
- New features
- Performance improvements
- Code refactoring
- Example sketches

#### Documentation
- README improvements
- Tutorial creation
- Translation to other languages
- Wiring diagram improvements
- Video tutorials

#### Testing
- Testing on different hardware
- Reporting compatibility issues
- Creating test cases
- Validating bug fixes

#### Community
- Answering questions in issues
- Helping newcomers
- Sharing your builds
- Writing blog posts

## Development Guidelines

### Code Style

#### Naming Conventions

- **Constants**: Use UPPER_SNAKE_CASE
  ```cpp
  const int MIDI_VELOCITY = 127;
  #define MAX_KEYS 32
  ```

- **Variables**: Use camelCase
  ```cpp
  int keyPressed = 0;
  boolean messageSent = false;
  ```

- **Functions**: Use camelCase with descriptive names
  ```cpp
  void initializeColumnPins() { }
  int getMidiNote(int row, int col) { }
  ```

- **Arrays**: Use camelCase with descriptive names
  ```cpp
  int keyValues[NUM_ROWS][NUM_COLS];
  boolean keyPressed[NUM_ROWS][NUM_COLS];
  ```

#### Formatting

- **Indentation**: 2 spaces (no tabs)
- **Braces**: Opening brace on same line
  ```cpp
  if (condition) {
    // code
  }
  ```

- **Line length**: Keep lines under 100 characters when possible

#### Comments

- Use `//` for single-line comments
- Use `/* */` for multi-line comments
- Add function documentation:
  ```cpp
  /**
   * Calculate MIDI note number for a given matrix position
   * @param row Row index (0-3)
   * @param col Column index (0-7)
   * @return MIDI note number
   */
  int getMidiNote(int row, int col) {
    return STARTING_MIDI_NOTE + (row * NUM_COLS) + col + 1;
  }
  ```

### Arduino-Specific Guidelines

- **Avoid using `String`**: Use char arrays for memory efficiency
- **Minimize global variables**: Use local variables when possible
- **Use `const` and `#define`**: For values that don't change
- **Avoid `delay()`**: Use `millis()` for timing when possible
- **Check array bounds**: Prevent buffer overflows

### Testing

Before submitting code:

1. **Compile without errors** on Arduino IDE
2. **Test on actual hardware** if possible
3. **Verify MIDI output** works correctly
4. **Check memory usage**: Use Arduino IDE memory report
5. **Run example sketches** to ensure compatibility

### Documentation

When adding features:

1. **Update README.md** with new functionality
2. **Update config.h** if adding configuration options
3. **Add comments** explaining complex logic
4. **Update CHANGELOG.md** with your changes
5. **Create examples** if adding major features

## Submitting Changes

### Pull Request Process

1. **Update your fork** with latest upstream changes:
   ```bash
   git fetch upstream
   git rebase upstream/main
   ```

2. **Make your changes** in your feature branch

3. **Test thoroughly** (see Testing section above)

4. **Commit your changes** with clear messages:
   ```bash
   git add .
   git commit -m "Add velocity sensitivity feature"
   ```

5. **Push to your fork**:
   ```bash
   git push origin feature/your-feature-name
   ```

6. **Create Pull Request** on GitHub:
   - Use a clear, descriptive title
   - Describe what changes you made and why
   - Reference any related issues
   - Include screenshots/videos if relevant

### Commit Message Guidelines

Use clear, descriptive commit messages:

**Good examples:**
```
Add velocity sensitivity based on press speed
Fix key ghosting issue in matrix scanning
Update wiring diagram with diode placement
Optimize loop performance by 30%
```

**Bad examples:**
```
Update file
Fix bug
Changes
asdf
```

### Pull Request Template

When creating a PR, include:

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Documentation update
- [ ] Performance improvement

## Testing
- [ ] Tested on Arduino Leonardo
- [ ] Tested with MIDI software
- [ ] Examples still work
- [ ] No compilation errors

## Checklist
- [ ] Code follows style guidelines
- [ ] Documentation updated
- [ ] CHANGELOG.md updated
- [ ] No breaking changes (or documented)
```

## Reporting Bugs

### Before Reporting

1. **Search existing issues** to avoid duplicates
2. **Test with latest version** of the code
3. **Verify hardware setup** is correct
4. **Try example sketches** to isolate the issue

### Bug Report Template

Use this template when reporting bugs:

```markdown
## Bug Description
Clear description of the bug

## Steps to Reproduce
1. Upload sketch to Arduino
2. Connect to MIDI software
3. Press key [X]
4. Observe behavior

## Expected Behavior
What should happen

## Actual Behavior
What actually happens

## Hardware
- Arduino Board: Leonardo
- Arduino IDE Version: 1.8.19
- MIDIUSB Library Version: 1.0.5
- Operating System: Windows 10

## Additional Context
- Screenshots
- Serial Monitor output
- Analog readings
- Photos of wiring (if relevant)
```

## Suggesting Features

### Feature Request Template

```markdown
## Feature Description
Clear description of the feature

## Use Case
Why this feature would be useful

## Proposed Implementation
How you think it could be implemented (optional)

## Alternatives Considered
Other ways to achieve the same goal (optional)

## Additional Context
Any other relevant information
```

### Good Feature Suggestions

- **Specific**: Clearly describe what you want
- **Useful**: Explain who would benefit and why
- **Feasible**: Consider Arduino hardware limitations
- **Compatible**: Won't break existing functionality

## Development Workflow

### Typical Contribution Flow

1. **Find or create an issue** describing what you'll work on
2. **Discuss approach** in the issue comments
3. **Fork and clone** the repository
4. **Create feature branch** from main
5. **Make changes** following guidelines above
6. **Test thoroughly** on real hardware
7. **Update documentation**
8. **Submit pull request**
9. **Address review feedback**
10. **Celebrate** when merged! 🎉

### Working on Issues

- **Comment on the issue** before starting work
- **Ask questions** if anything is unclear
- **Update progress** in issue comments
- **Link PR to issue** when submitting

## Code Review Process

### What to Expect

- Reviews typically happen within 1 week
- Reviewers may request changes
- Be patient and responsive to feedback
- Multiple rounds of review may be needed

### As a Reviewer

- Be kind and constructive
- Explain the reasoning for suggestions
- Approve when changes look good
- Thank contributors for their work

## Release Process

### Versioning

We use [Semantic Versioning](https://semver.org/):

- **Major** (X.0.0): Breaking changes
- **Minor** (0.X.0): New features, backwards compatible
- **Patch** (0.0.X): Bug fixes

### Release Checklist

Before releasing a new version:

- [ ] All tests pass
- [ ] Documentation updated
- [ ] CHANGELOG.md updated
- [ ] Version numbers updated
- [ ] Examples tested
- [ ] README reflects new features
- [ ] Tag created in git

## Getting Help

### Resources

- **GitHub Issues**: Ask questions, report bugs
- **README.md**: User documentation
- **examples/**: Code examples
- **docs/**: Technical documentation

### Questions?

Don't hesitate to ask! Common ways:

1. **Open an issue** with "Question" label
2. **Comment on relevant issue** if related
3. **Check existing issues** for similar questions

## License

By contributing, you agree that your contributions will be licensed under the MIT License, the same license as the project.

## Recognition

### Contributors

All contributors will be recognized in:
- GitHub contributors page
- Future CONTRIBUTORS.md file (when created)
- Release notes for significant contributions

### Attribution

If you use significant portions of code from other sources:
- Include original license/attribution
- Document in comments
- List in acknowledgments

---

## Thank You!

Every contribution, no matter how small, helps make this project better. We appreciate your time and effort!

**Happy contributing! 🎹🎵**

---

## Quick Links

- [Project README](README.md)
- [Wiring Guide](docs/WIRING.md)
- [Examples](examples/README.md)
- [Changelog](CHANGELOG.md)
- [License](LICENSE)
