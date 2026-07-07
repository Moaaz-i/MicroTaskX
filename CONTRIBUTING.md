# Contributing to MicroTaskX

Thank you for helping us improve the MicroTaskX library! This guide outlines the process for reporting issues, suggesting features, and contributing code to the repository.

We love community contributions. By participating in this project, you help make multitasking on microcontrollers easier and more efficient for everyone.

---

## 1. How to Report Issues (Bug Reports & Feature Requests)

Before opening a new issue, please search the existing open issues and discussions to ensure it hasn't been reported or solved already.

### Submitting a Bug Report

When submitting an issue, please use a clear title and provide as much detail as possible to help us reproduce and fix the bug:

1. **Hardware & Environment:** Specify the microcontroller used (e.g., ESP32, Arduino Uno, STM32) and your development environment (e.g., PlatformIO, Arduino IDE 2.x).
2. **Library Version:** Mention the exact version of `MicroTaskX` you are using.
3. **Description:** Describe what you expected to happen versus what actually occurred.
4. **Minimal Reproducible Example:** Provide a concise, minimal snippet of code that demonstrates the bug. Please format it using code blocks:
   \`\`\`cpp
   // Your minimal code here
   \`\`\`

### Submitting a Feature Request

Have an idea to make MicroTaskX faster or more robust?

- Explain clearly why this feature would be useful to your development or the broader community.
- Provide a conceptual example of the proposed API design or syntax if possible.

---

## 2. How to Contribute Code

Want to fix an issue, add an example, or optimize the task scheduler? Follow these steps to submit your changes:

1. **Fork the Repository:** Create your own copy of the codebase.
2. **Create a Branch:** Work on a descriptive branch name (e.g., `fix/task-scheduler-overflow` or `feature/mutex-support`).
3. **Follow Coding Standards:** Ensure your code is properly commented, clean, and respects the non-blocking execution architecture of the library.
4. **Add Examples:** If you are adding a major feature, update the documentation or include a quick script under the `/examples` directory.
5. **Submit a Pull Request (PR):** Describe your changes in detail within the PR description and reference the specific issue number being resolved (e.g., `Closes #12`).

> 💡 **Tip for First-Time Contributors:** Look out for GitHub issues tagged with `good first issue`. These are smaller, beginner-friendly tasks designed to help you get familiar with the core logic of MicroTaskX.

---

## 3. Need Help or General Discussion?

- For general architecture questions, sharing your projects, or asking for usage help, please open a thread in the **GitHub Discussions** section instead of opening a bug issue.
- Feel free to join our community chat (Discord/Telegram link if available) to discuss ideas in real-time!
