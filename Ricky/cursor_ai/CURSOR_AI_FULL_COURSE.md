# Full Course: How to Use Cursor AI

A detailed guide to using [Cursor](https://cursor.com/)—the AI-powered code editor and coding agent. This course is based on official Cursor documentation, [Cursor Docs](https://docs.cursor.com/), and [Cursor Learn](https://cursor.com/learn).

---

## Table of Contents

1. [Introduction & Getting Started](#1-introduction--getting-started)
2. [Core Concepts](#2-core-concepts)
3. [Agent: Your AI Coding Partner](#3-agent-your-ai-coding-partner)
4. [Agent Modes](#4-agent-modes)
5. [Tab: Smart Autocomplete](#5-tab-smart-autocomplete)
6. [Inline Edit (Cmd/Ctrl+K)](#6-inline-edit-cmdctrlk)
7. [Context & @ Mentions](#7-context--mentions)
8. [Rules: Persistent Instructions](#8-rules-persistent-instructions)
9. [Keyboard Shortcuts](#9-keyboard-shortcuts)
10. [Prompting Best Practices](#10-prompting-best-practices)
11. [Common Workflows](#11-common-workflows)
12. [AI Foundations (How It Works)](#12-ai-foundations-how-it-works)
13. [Resources & Next Steps](#13-resources--next-steps)

---

## 1. Introduction & Getting Started

### What is Cursor?

Cursor is an **AI editor and coding agent**. You describe what you want to build or change in natural language, and Cursor writes and edits code for you. It combines:

- **Editor**: VS Code–based IDE with full code editing.
- **Agent**: An AI that can search the codebase, edit files, run terminal commands, and fix errors.
- **Tab**: Multi-line autocomplete that predicts your next edits.
- **Inline Edit**: Edit selected code with natural language (Cmd/Ctrl+K).

### Quickstart

1. **Download & install**  
   Get Cursor from [cursor.com/download](https://cursor.com/download) (macOS, Windows, Linux).

2. **Open the Agent**  
   - **Shortcut**: `Cmd+I` (Mac) or `Ctrl+I` (Windows/Linux).  
   - Agent appears in the side panel and can explore your codebase, edit files, and run commands.

3. **First prompt**  
   Try: *"How does this project work?"*  
   Agent will explore the repo, read relevant files, and explain the architecture.

4. **Plan before building**  
   Press **Shift+Tab** in the agent input to toggle **Plan Mode**. Agent will:
   - Research the codebase
   - Ask clarifying questions
   - Create an implementation plan
   - Wait for your approval before writing code  

   Save plans to `.cursor/plans/` via "Save to workspace."

5. **Let Agent find context**  
   You don’t need to tag every file. Describe what you need (e.g. "the authentication flow"); Agent uses search to find relevant files. Use `@` only when you know the exact file or folder.

6. **Write specific prompts**  
   Vague: *"add tests for auth.ts"*  
   Better: *"Write a test case for auth.ts covering the logout edge case, using the patterns in `__tests__/` and avoiding mocks."*

7. **When to start a new chat**  
   - New chat when: new task, Agent is confused, or you’ve finished one unit of work.  
   - Same chat when: iterating on the same feature or debugging what Agent just built.  
   Use `@Past Chats` to reference earlier work in a new conversation.

8. **Review and iterate**  
   - Watch the diff view as Agent edits.  
   - Press **Escape** to stop and redirect if needed.  
   - After Agent finishes: **Review → Find Issues** to run a review pass on the changes.

9. **Verifiable goals**  
   - Use typed languages so the type checker gives feedback.  
   - Write tests so Agent can run them and iterate until they pass.  
   - Use linters for style and quality.

---

## 2. Core Concepts

| Concept | Description |
|--------|-------------|
| **Tab** | Multi-line code completion. Press **Tab** to accept; suggestions adapt to current code and recent changes. |
| **Agent** | AI that reads and modifies code across files. You describe changes in natural language; Agent executes them. |
| **Inline Edit** | Edit selected code with natural language. **Cmd+K** / **Ctrl+K**, describe the change, see it applied in place. |
| **Chat** | AI chat with multiple tabs, history, checkpoints, and export. |
| **Rules** | Persistent instructions (coding standards, frameworks, project conventions) that shape Agent behavior. |
| **Semantic Search** | Find code by meaning, not just text. Powers natural-language search and context-aware suggestions. |
| **MCP** | Model Context Protocol—connect external tools (databases, APIs, docs). |
| **Context** | What the model sees: files, symbols, conversation history. |
| **Models** | Different AI models (speed, capability, cost). Choose in the model picker. |

---

## 3. Agent: Your AI Coding Partner

### How to Open Agent

- **Cmd+I** / **Ctrl+I** — Toggle Agent side panel (or use **Cmd+L** / **Ctrl+L** depending on binding).

### How Agent Works

Agent is built from:

1. **Instructions** — System prompt + [Rules](#8-rules-persistent-instructions).
2. **Tools** — Edit files, search codebase, run terminal, browser, etc.
3. **Your messages** — Prompts and follow-ups that direct the work.

### Agent Tools

- **Semantic search** — Find code by meaning.
- **Search files and folders** — Text/path search.
- **Web** — Fetch information from the web.
- **Fetch Rules** — Load project/user rules.
- **Read files** — Open and read files.
- **Edit files** — Create and modify files.
- **Run shell commands** — Execute commands in the terminal.
- **Browser** — Control a browser (e.g. for testing).
- **Image generation** — Generate images when needed.
- **Ask questions** — Clarify with you when needed.

There is no fixed limit on how many tool calls Agent can make for a task.

### Message Summarization

Long chats are summarized so context stays manageable. Use **/summarize** in chat to manually compress the conversation when it gets long.

### Checkpoints

- **Checkpoints** = automatic snapshots of Agent’s edits.
- Use **Restore Checkpoint** (on a previous request or the + on a message) to undo Agent’s changes.
- Stored locally, separate from Git. Use Git for real version control; checkpoints for quick rollback of Agent work.

### Export & Share

- **Export**: Context menu → "Export Chat" → Markdown file.
- **Share**: Read-only link; others can view and fork the conversation (paid plan; some secrets auto-redacted; disabled in Privacy Mode).

### Queued Messages

- **Enter** — Add message to the queue (runs after Agent finishes the current task).
- **Cmd+Enter** / **Ctrl+Enter** — Send immediately, bypassing the queue (good for urgent follow-ups or redirecting).

---

## 4. Agent Modes

Switch modes from the mode picker or **Cmd+.** / **Ctrl+.**.

| Mode | Best for | What it does |
|------|----------|---------------|
| **Agent** | Complex features, refactors | Full autonomy: search, multi-file edits, terminal, all tools. |
| **Ask** | Learning, planning, Q&A | Read-only. Search only; no edits. |
| **Plan** | Big, ambiguous features | Asks questions, researches, writes a plan, then you approve before building. Toggle with **Shift+Tab** in the input. |
| **Debug** | Tricky bugs, regressions | Hypotheses, log instrumentation, reproduction steps, log analysis, then a targeted fix. |

### Plan Mode in Detail

1. Agent asks clarifying questions.
2. Researches the codebase.
3. Writes an implementation plan (ephemeral or save to `.cursor/plans/`).
4. You review and edit the plan.
5. You click to build when ready.

Use Plan Mode for: complex features, many files, unclear requirements, or when you want to review the approach before code.

### Debug Mode in Detail

1. **Explore & hypothesize** — Agent reads code and lists possible causes.
2. **Add instrumentation** — Logs that send data to a local debug server (Cursor extension).
3. **Reproduce** — You follow steps; Agent captures runtime behavior.
4. **Analyze logs** — Agent finds root cause from logs.
5. **Targeted fix** — Small, focused code change.
6. **Verify & cleanup** — You re-run; Agent removes instrumentation.

Best for: reproducible-but-mysterious bugs, race conditions, performance/memory issues, regressions.

### Custom Slash Commands

For custom workflows, use **custom slash commands** (e.g. `/pr`, `/fix-issue`) instead of deprecated custom modes. Define them in `.cursor/commands/` and trigger with `/` in the agent input.

---

## 5. Tab: Smart Autocomplete

**Tab** is Cursor’s autocomplete model. It can:

- Suggest multi-line edits.
- Add missing imports (TypeScript, Python).
- Suggest jumps within a file and across files for coordinated edits.
- Use recent changes, linter errors, and accepted edits.

### Using Tab

- **Ghost text** when adding code; **diff popup** when modifying existing code.
- **Tab** — Accept suggestion.
- **Escape** — Reject.
- **Cmd+→** / **Ctrl+→** — Accept next word (partial accept).
- Keep typing or press Escape to hide the suggestion.

### Jump in File / Across Files

- After accepting an edit, press **Tab** again to jump to the next suggested edit location.
- For cross-file edits, a portal window can appear at the bottom.

### Auto-import

- In TypeScript/Python, use a symbol from another file; Tab suggests the import. Accept to add it.
- If it doesn’t work: check language server/extensions; try **Cmd+.** / **Ctrl+.** for Quick Fix.

### Tab in Peek

- Tab works in **Go to Definition** / **Go to Type Definition** peek views—useful for changing signatures and call sites.

### Settings (Cursor Settings → Tab)

- **Snooze** — Disable Tab for a period (status bar).
- **Disable globally** or **for specific file extensions** (e.g. markdown, JSON).

---

## 6. Inline Edit (Cmd/Ctrl+K)

- **Cmd+K** / **Ctrl+K** — Open inline edit.
- Select code, then describe the change in natural language; Cursor applies it in place.
- **Cmd+Shift+K** / **Ctrl+Shift+K** — Toggle input focus.
- **Enter** — Submit.
- **Cmd+Shift+Backspace** / **Ctrl+Shift+Backspace** — Cancel.
- **Alt+Enter** — Ask a quick question.

Use this for local, targeted edits without opening the full Agent panel.

---

## 7. Context & @ Mentions

Context is what the model sees: files, folders, code snippets, docs, and chat history. **@** lets you attach specific context.

### @ Files & Folders

- Type **@** then **Files & Folders** (or start typing a path).
- Select a file or folder to add it to context.
- You can also drag files from the sidebar into the Agent input.
- For folders, type **/** to go deeper; large files/folders are condensed to fit context limits.

### @ Code

- **@Code** — Reference a specific code section (symbol or selection) instead of a whole file.

### @ Docs

- **@Docs** — Use documentation in chat. Cursor includes popular docs; you can add custom docs by URL.
- **Add doc**: `@Docs` → "Add new doc" → paste URL. Manage in **Cursor Settings → Indexing & Docs**; optional "Share with team."

### Built-in Commands

- **/summarize** — Compress the conversation and summarize.
- You can define [custom slash commands](https://cursor.com/docs/agent/chat/commands) for repeated workflows.

### Context Tips

- If you know the exact file, use **@**. If not, describe what you need and let Agent search.
- Avoid tagging lots of irrelevant files; it can dilute what’s important.

---

## 8. Rules: Persistent Instructions

**Rules** are system-level instructions that apply across chats. They’re included at the start of the model context so the AI behaves consistently.

### Rule Types

| Type | When applied |
|------|----------------|
| **Project Rules** | In `.cursor/rules` (or subfolders); version-controlled; can use globs/descriptions. |
| **User Rules** | In Cursor Settings → Rules; apply in all projects. |
| **Team Rules** | From dashboard; for Team/Enterprise; can be required for everyone. |
| **AGENTS.md** | Single markdown file in project root (or subdirs); no metadata. |

### Project Rules

- Stored in `.cursor/rules` as `.md` or `.mdc`.
- `.mdc` can have frontmatter: `description`, `globs`, `alwaysApply`.
- Rule types:
  - **Always Apply** — Every chat.
  - **Apply Intelligently** — When Agent decides it’s relevant (from description).
  - **Apply to Specific Files** — When the active/file path matches globs.
  - **Apply Manually** — When you @-mention the rule.

Example frontmatter:

```yaml
---
globs: ["**/*.ts"]
alwaysApply: false
---
Use our internal RPC pattern. Prefer snake_case for service names.
```

Create rules: **New Cursor Rule** or **Cursor Settings → Rules, Commands**.

### Best Practices for Rules

- Keep rules focused, actionable, and scoped; under ~500 lines; split into multiple rules if needed.
- Prefer pointing to examples in the repo over pasting long code.
- Don’t duplicate linter rules or common tool docs; don’t document every rare edge case.
- Add rules when Agent keeps making the same mistake; check them into git so the team benefits.

### AGENTS.md

Plain markdown in project root (or subdirs). Example:

```markdown
# Project Instructions
## Code Style
- Use TypeScript for all new files.
- Prefer functional components in React.
## Architecture
- Follow the repository pattern.
- Keep business logic in service layers.
```

### User Rules

Global preferences in **Cursor Settings → Rules**, e.g.:

- "Reply concisely. Avoid repetition and filler."

### Team Rules

- Created in [Cursor dashboard](https://cursor.com/dashboard?tab=team-content).
- Can be **required** so members can’t disable them.
- Precedence: **Team → Project → User**.

### Importing Rules

- **Remote (GitHub)**: Settings → Rules → "+ Add Rule" → Remote Rule (Github) → paste repo URL. Rules stay synced.
- **Agent Skills**: Optional rules from the Skills ecosystem; applied when Agent decides they’re relevant.

---

## 9. Keyboard Shortcuts

View all: **Cmd+R** / **Ctrl+R** then **Cmd+S** / **Ctrl+S**, or **Cmd+Shift+P** / **Ctrl+Shift+P** → "Keyboard Shortcuts."

### General

| Shortcut | Action |
|----------|--------|
| **Cmd+I** / **Ctrl+I** | Toggle Agent side panel |
| **Cmd+L** / **Ctrl+L** | Toggle side panel (if not bound to mode) |
| **Cmd+E** / **Ctrl+E** | Toggle Agent layout |
| **Cmd+.** / **Ctrl+.** | Mode menu |
| **Cmd+/** / **Ctrl+/** | Cycle AI models |
| **Cmd+Shift+J** / **Ctrl+Shift+J** | Cursor settings |
| **Cmd+Shift+Space** / **Ctrl+Shift+Space** | Voice mode |
| **Cmd+,** / **Ctrl+,** | General settings |
| **Cmd+Shift+P** / **Ctrl+Shift+P** | Command palette |

### Chat

| Shortcut | Action |
|----------|--------|
| **Enter** | Nudge (default) / queue message |
| **Ctrl+Enter** | Queue message |
| **Cmd+Enter** / **Ctrl+Enter** (while typing) | Force send (bypass queue) |
| **Cmd+Shift+Backspace** / **Ctrl+Shift+Backspace** | Cancel generation |
| **Cmd+Shift+L** / **Ctrl+Shift+L** (with selection) | Add selection to chat |
| **Cmd+V** / **Ctrl+V** (code/log in clipboard) | Add clipboard as context |
| **Cmd+Shift+V** / **Ctrl+Shift+V** | Add clipboard to input |
| **Cmd+Enter** / **Ctrl+Enter** (with suggested changes) | Accept all changes |
| **Cmd+Backspace** / **Ctrl+Backspace** | Reject all changes |
| **Tab** | Next message |
| **Shift+Tab** | Rotate Agent modes |
| **Cmd+Opt+/** / **Ctrl+Alt+/** | Model toggle |
| **Cmd+N** / **Ctrl+N** or **Cmd+R** / **Ctrl+R** | New chat |
| **Cmd+T** / **Ctrl+T** | New chat tab |
| **Cmd+[** / **Ctrl+[** | Previous chat |
| **Cmd+]** / **Ctrl+]** | Next chat |
| **Cmd+W** / **Ctrl+W** | Close chat |
| **Escape** | Unfocus input |

### Inline Edit

| Shortcut | Action |
|----------|--------|
| **Cmd+K** / **Ctrl+K** | Open inline edit |
| **Cmd+Shift+K** / **Ctrl+Shift+K** | Toggle input focus |
| **Enter** | Submit |
| **Cmd+Shift+Backspace** / **Ctrl+Shift+Backspace** | Cancel |
| **Alt+Enter** | Quick question |

### Code & Context

| Shortcut | Action |
|----------|--------|
| **@** | Open @ mentions |
| **/** | Slash commands |
| **Cmd+Shift+L** / **Ctrl+Shift+L** | Add selection to Chat |
| **Cmd+Shift+K** / **Ctrl+Shift+K** | Add selection to Inline Edit |
| **Cmd+L** / **Ctrl+L** | Add selection to new chat |
| **Cmd+M** / **Ctrl+M** | Toggle file reading strategies |
| **Cmd+→** / **Ctrl+→** | Accept next word of suggestion |
| **Cmd+Enter** / **Ctrl+Enter** | Search codebase in chat |
| Copy code → **Cmd+V** / **Ctrl+V** | Add as context; **Cmd+Shift+V** / **Ctrl+Shift+V** as text |

### Tab

| Shortcut | Action |
|----------|--------|
| **Tab** | Accept suggestion |
| **Cmd+→** / **Ctrl+→** | Accept next word |

### Terminal

| Shortcut | Action |
|----------|--------|
| **Cmd+K** / **Ctrl+K** | Open terminal prompt bar |
| **Cmd+Enter** / **Ctrl+Enter** | Run generated command |
| **Escape** | Accept command |

---

## 10. Prompting Best Practices

### Be Specific

| Vague | Specific |
|-------|----------|
| "add tests for auth.ts" | "Write a test for auth.ts covering the logout edge case, using patterns in `__tests__/`, no mocks" |
| "fix the bug" | "Login form submits twice on button click. Find the cause and fix it." |

### Plan for Big Tasks

- Use **Plan Mode** (Shift+Tab) for complex or multi-file work.
- Review and refine the plan before building; revert and re-plan if the result is wrong instead of only patching in chat.

### Give Verifiable Goals

- Typed languages, tests, and linters give Agent a clear target and fast feedback.

### Use the Right Mode

- **Ask** for understanding only.
- **Plan** for unclear or large scope.
- **Agent** for implementation.
- **Debug** for hard-to-find bugs.

### Manage Context

- Don’t overload with irrelevant @ files; let Agent search when you don’t know exact locations.
- Start a new chat for a new task; use `@Past Chats` to refer to prior work.

---

## 11. Common Workflows

### Test-Driven Development (TDD)

1. Ask Agent to **write tests** (expected inputs/outputs). Say you’re doing TDD so it doesn’t implement the feature yet.
2. **Run tests and confirm they fail.**
3. **Commit the tests.**
4. Ask Agent to **implement to pass the tests**, without changing tests; iterate until green.
5. **Commit the implementation.**

### Git / PR with Commands

- Put commands in `.cursor/commands/` (e.g. `pr/COMMAND.md`, `fix-issue/COMMAND.md`).
- Trigger with `/pr`, `/fix-issue 123`, etc.
- Example: "Create a PR: look at diff, write commit message, commit, push, run `gh pr create`, return PR URL."

### Codebase Understanding

Ask like a teammate:

- "How does logging work in this project?"
- "How do I add a new API endpoint?"
- "Walk me through what happens when a user submits the login form."

Go from broad to narrow: overview → subsystem → specific flow → specific line.

### Architecture Diagrams

- "Create a Mermaid diagram of the data flow for our auth system, including OAuth, session management, and token refresh."

### Design to Code

- Paste a screenshot or mockup into the agent input.
- Ask Agent to implement the component; use the browser sidebar to preview and iterate.
- For visual bugs, paste a screenshot of the wrong state.

### Long-Running Loops (Hooks)

- Use [Agent Hooks](https://cursor.com/docs/agent/hooks) (e.g. in `.cursor/hooks.json`) to run Agent until a condition (e.g. all tests pass) or max iterations.

### Cloud Agents

- Use [Cloud agents](https://cursor.com/agents) for background tasks: bug fixes, refactors, tests, docs. Start from the editor, cursor.com/agents, or phone; they run in remote sandboxes. Slack: "@Cursor" to trigger.

---

## 12. AI Foundations (How It Works)

From [Cursor Learn](https://cursor.com/learn):

- **Probabilistic, not deterministic** — Same prompt can yield different outputs. Don’t assume identical results every time.
- **Models differ** — Speed, cost, and capability vary. Choose the model that fits the task (see [Models](https://cursor.com/docs/models)).
- **Modalities** — Text, images (mockups, screenshots), and voice can all be used; Cursor uses these for coding tasks.
- **Context** — What you send (files, @ mentions, chat history) shapes the response. [Cursor Learn: Context](https://cursor.com/learn/context).
- **Tool calling** — Agent uses tools (search, read, edit, terminal, etc.). [Cursor Learn: Tool calling](https://cursor.com/learn/tool-calling).
- **Agents** — Autonomous loop: plan → use tools → act → repeat. [Cursor Learn: Agents](https://cursor.com/learn/agents).

Further topics on Cursor Learn: [Hallucination & limitations](https://cursor.com/learn/hallucination-limitations), [Tokens & pricing](https://cursor.com/learn/tokens-pricing).

---

## 13. Resources & Next Steps

### Official Links

- **Cursor**: [cursor.com](https://cursor.com/)
- **Docs**: [docs.cursor.com](https://docs.cursor.com/)
- **Learn**: [cursor.com/learn](https://cursor.com/learn)
- **Changelog**: [cursor.com/changelog](https://cursor.com/changelog)
- **Download**: [cursor.com/download](https://cursor.com/download)
- **Models**: [cursor.com/docs/models](https://cursor.com/docs/models)
- **Pricing**: [cursor.com/docs/account/pricing](https://cursor.com/docs/account/pricing)

### Docs to Explore

- [Agent Overview](https://cursor.com/docs/agent/overview) — Tools, checkpoints, queue.
- [Agent Modes](https://cursor.com/docs/agent/modes) — Agent, Ask, Plan, Debug.
- [Tab](https://cursor.com/docs/tab/overview) — Autocomplete, jumps, auto-import.
- [Rules](https://cursor.com/docs/context/rules) — Project, user, team, AGENTS.md.
- [@ Mentions](https://cursor.com/docs/context/mentions) — Files, Code, Docs.
- [Commands](https://cursor.com/docs/agent/chat/commands) — Custom slash commands.
- [Keyboard Shortcuts](https://cursor.com/docs/configuration/kbd) — Full list.
- [Cookbook](https://cursor.com/docs/cookbook/agent-workflows) — TDD, git, codebase understanding, diagrams, design-to-code, hooks, cloud agents.
- [Integrations](https://cursor.com/docs/integrations/slack) — Slack, GitHub, Linear, Git, GitLab, deeplinks.
- [Troubleshooting](https://cursor.com/docs/troubleshooting/common-issues) — Common issues and request reporting.

### Community & Support

- **Forum**: [forum.cursor.com](https://forum.cursor.com)
- **Support**: [hi@cursor.com](mailto:hi@cursor.com) (account/billing)

---

*This course is a synthesis of Cursor’s official documentation and Learn material. For the latest behavior and features, always refer to [docs.cursor.com](https://docs.cursor.com) and [cursor.com/changelog](https://cursor.com/changelog).*
