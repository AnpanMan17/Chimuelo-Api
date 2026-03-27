# 📋 EOP Issue Template — Exodus Ops Platform

> **Binding Contract Notice:** Adding this issue to the EOP board implies it is part of the product
> scope, will be evaluated under engineering criteria, and must comply with all standards defined in
> the SWAgreement. Incomplete issues (missing mandatory fields) are excluded from evaluation.

---

## 📌 Issue Metadata

<!-- ═══════════════════════════════════════════════════════════════════
     ALL fields marked ✅ MANDATORY are required. Issues with missing
     mandatory fields are INCOMPLETE and will be excluded from evaluation.
     ═══════════════════════════════════════════════════════════════════ -->

| Field              | Value |
|--------------------|-------|
| **Workflow Status** ✅ | `Triage` |
| **Team** ✅          | <!-- Catalyst / Hyperion / Nexus / Orion --> |
| **Milestone** ✅     | <!-- M0 — Product Discovery / M1 — Core Communication Layer / M2 — Processing Capability / M3 — Product API & Integration / M4 — Edge & IoT Integration --> |
| **Priority** ✅      | <!-- Urgent / High / Medium / Low --> |
| **Size** ✅          | <!-- XS (<1d) / S (1–2d) / M (3–5d) / L (6–10d) / XL (>10d) --> |
| **Estimated Days** ✅ | <!-- e.g. 2 --> |
| **Target Date** ✅   | <!-- YYYY-MM-DD --> |
| **Assigned To**     | <!-- @github-handle --> |
| **Branch**          | <!-- feature/<issue-number_short-description> --> |
| **Notes**           | <!-- Optional context, dependencies, or risk flags --> |

---

## 🏷️ Traceability

> **Principle:** Every feature must trace to a documented requirement.
> Every architectural decision must have a corresponding ADR.

| Link              | Reference |
|-------------------|-----------|
| **Requirement ID** | <!-- e.g. US-101, NFR-1 → PRD-EOP-2077-001 --> |
| **ADR Reference**  | <!-- e.g. ADR-001, ADR-003 → /docs/adr/ --> |
| **Related Issues** | <!-- #issue-number --> |
| **Epic**           | <!-- E1 / E2 / ... / E13 --> |

---

## 📖 User Story

```
As a <persona: Vault Operator / Network Analyst / Integration Engineer / Edge Device>,
I want to <action / capability>,
So that <business value / outcome>.
```

---

## 🎯 Acceptance Criteria

> Each AC must be verifiable with an **automated test** or a **reproducible demo**.
> Vague or untestable criteria are not acceptable.

- [ ] **AC1.** <!-- Specific, measurable, testable criterion -->
- [ ] **AC2.** <!-- ... -->
- [ ] **AC3.** <!-- ... -->
- [ ] **AC4.** <!-- ... -->
<!-- Add more as needed. Remove any AC that does not apply. -->

---

## 🏗️ Design Artifacts

> **Principle: Design precedes implementation.**
> No code is written before the design is documented.
> This section must be completed before moving to `In Progress`.

### ADR Required?

- [ ] **Yes** — ADR document created at `/docs/adr/ADR-XXX-<title>.md` and linked above.
- [ ] **No** — Justified below:

> _Justification (if no ADR):_ <!-- e.g. "Implementation task; architectural decision already covered by ADR-002" -->

### Design Checklist (complete before implementation)

- [ ] Component boundaries and responsibilities defined
- [ ] Interface / API contract specified (message types, function signatures, REST endpoints)
- [ ] Sequence diagram or interaction diagram created (if applicable)
- [ ] Concurrency model documented (if applicable)
- [ ] Error-handling strategy defined (error codes, failure modes)
- [ ] Observability design included: OTel spans, structured log fields, metrics exposed

---

## ⚙️ Technical Scope

### What this issue DOES
<!-- One paragraph. Be specific about the deliverable. -->

### What this issue DOES NOT DO
<!-- Explicit non-scope prevents scope creep and clarifies integration contracts. -->

### Dependencies
<!-- Which other squads' services or issues does this depend on? What is assumed about their behavior? -->

| Dependency        | Type              | Status |
|-------------------|-------------------|--------|
| <!-- ADR / Issue / Squad service --> | <!-- Blocking / Non-blocking --> | <!-- Open / Resolved --> |

---

## 🧪 Testing Requirements

> Minimum test coverage: **90%** on business logic.
> Trivial or superficial tests are **prohibited**.
> CI must pass on all commits before merge.

- [ ] **Unit tests** cover: <!-- list specific cases, edge cases, error paths -->
- [ ] **Integration tests** cover: <!-- end-to-end flow, cross-squad interop if applicable -->
- [ ] **Load / concurrency tests** cover: <!-- if applicable per NFR-1 -->
- [ ] **Memory safety:** AddressSanitizer / Valgrind reports zero errors
- [ ] **Thread safety:** ThreadSanitizer reports zero data races
- [ ] **Static analysis:** clang-tidy zero warnings, cppcheck clean, SonarQube zero findings

---

## 📦 Deliverables Checklist

> A task may only be closed when **all** of the following are satisfied.

### Code Quality
- [ ] `clang-format` compliance verified (`.clang-format` applied, CI passes)
- [ ] `clang-tidy` — zero warnings, zero errors
- [ ] `cppcheck` / `scan-build` — zero findings
- [ ] `valgrind` / ASan / TSan — zero memory leaks, zero uninitialized memory, zero data races
- [ ] No magic numbers — all literals defined as named constants
- [ ] No global variables
- [ ] No hardcoded credentials or configuration values
- [ ] All inputs validated and sanitized (user / file / network)
- [ ] RAII applied to all resources (sockets, file descriptors, memory, mutexes)
- [ ] C++ exceptions do not cross module boundaries (public interfaces use error codes / `std::expected`)

### Documentation
- [ ] All public `.hpp` files include Doxygen headers (`@file`, `@brief`, `@details`, `@param`, `@return`, `@pre`, `@post`)
- [ ] `.cpp` files include inline comments only (no Doxygen blocks)
- [ ] `README.md` updated: how to build, run locally, execute test suite
- [ ] `CHANGELOG.md` entry added for this change
- [ ] If an ADR was created or modified: linked from `README.md`, stored in `/docs/adr/`

### CI / CD
- [ ] CI pipeline is green (build + test + lint + sanitizers)
- [ ] Docker image builds successfully; runtime image ≤ 50 MB
- [ ] K8s manifests pass `kubeval` / `kubeconform` validation (if applicable)
- [ ] **At least one peer review approved** (reviewer ≠ author)

### Git Hygiene
- [ ] All commits are GPG-signed
- [ ] Each commit represents one logical change (no bulk commits)
- [ ] Commit messages follow [Conventional Commits](https://www.conventionalcommits.org/)
- [ ] Branch name follows schema: `feature/<issue-number_description>` or `fix/<issue-number_description>`
- [ ] No compiled binaries, libraries (`.so`, `.dll`), log files, or generated files committed
- [ ] Target branch is `release/<version>` — **direct commits to `main` are prohibited**

---

## 📢 In-Progress Updates

> **Required:** While this issue is `In Progress`, the assigned developer must post a progress
> update directly in this thread **at minimum each session**. Use the template below.

```markdown
# Update — YYYY-MM-DD

- **Work completed today:**
  -
- **Blockers encountered:**
  -
- **Next steps:**
  -
```

---

## ✅ Definition of Done

This issue is **Done** when ALL of the following are true:

1. [ ] Code is merged to the release branch with **CI fully green**
2. [ ] Every acceptance criterion above is verifiable with an automated test or a reproducible demo
3. [ ] If this issue made an architectural decision, the corresponding ADR is documented in `/docs/adr/`
4. [ ] No memory leaks or data races are introduced (verified by CI sanitizers)
5. [ ] The service `README.md` reflects the current state: build, run locally, test suite execution
6. [ ] `CHANGELOG.md` is updated with a meaningful entry for this change

---

---
---

# 🔴 M0 — Product Discovery: Supplementary Section

> **Use this section ONLY for issues belonging to Milestone M0.**
> M0 is the critical foundational milestone. The **Proto Freeze gate** (End of Week 2) is the first
> hard delivery gate. No squad advances to M1 without passing it.
>
> **Gate Criterion:** Protocol v1.0 documented and signed off by all four squads. PL + All squads.
>
> M0 failures cascade into every subsequent milestone. A missing ADR, an incomplete protocol
> definition, or undefined service boundaries will block M1 implementation. There are no exceptions.

---

## 🧭 M0 Scope Reference

M0 delivers the **Requirements, ADRs, and Architectural Baseline** for the entire project.

| M0 ADR           | Title                              | Owner            | Due       |
|------------------|------------------------------------|------------------|-----------|
| ADR-001          | IPC Mechanism — BSD Sockets        | All squads       | Week 1    |
| ADR-002          | Server Concurrency Model           | Individual squad | Week 1–2  |
| ADR-003          | Message Protocol Design            | All squads (collectively) | Week 2 — Proto Negotiation Meeting |
| ADR-004          | Service Boundaries                 | Individual squad | Week 1–2  |
| ADR-005          | Observability Strategy             | All squads       | Week 1    |
| ADR-006          | Containerization & K8s Adoption    | All squads       | Week 1    |

---

## 📐 M0 Design Checklist

> All items below must be completed **before any implementation code is written**.
> This is non-negotiable per the Engineering Contract (30% Design phase).

### ADR Completeness Verification

- [ ] **ADR-001 (IPC / BSD Sockets):** Accepted — stored in `/docs/adr/ADR-001-ipc-mechanism.md`
- [ ] **ADR-002 (Concurrency Model):** Squad's chosen model (Thread-per-connection / Thread Pool / epoll) documented with trade-off analysis. Stored in `/docs/adr/ADR-002-concurrency-model.md`
- [ ] **ADR-003 (Message Protocol):** All fields populated (framing, message envelope, payload encoding, message types, versioning policy). Stored in `/docs/adr/ADR-003-message-protocol.md`
- [ ] **ADR-004 (Service Boundaries):** Services owned listed; responsibilities, operations exposed/consumed, state owned, and guarantees provided documented. Stored in `/docs/adr/ADR-004-service-boundaries.md`
- [ ] **ADR-005 (Observability):** OTel SDK instrumentation plan defined; structured log format specified; span requirements listed. Stored in `/docs/adr/ADR-005-observability.md`
- [ ] **ADR-006 (Containerization):** Multi-stage Dockerfile plan, K8s manifest requirements, and local dev stack documented. Stored in `/docs/adr/ADR-006-containerization.md`

---

## 🤝 Proto Negotiation Meeting Readiness

> This checklist applies to issues that are part of the **Proto Negotiation Meeting** preparation
> (ADR-003). Each squad must arrive with the following prepared.

### Squad Preparation (complete before the meeting)

- [ ] **Operations to expose:** List of verbs, payloads, and expected responses this service provides
- [ ] **Operations to consume:** List of operations needed from other squads' services
- [ ] **Proposed message format:** Framing strategy (length-prefix or delimiter), field types, encoding (binary / JSON / custom) with trade-off rationale
- [ ] **Draft ADR-004:** Service Boundaries — what the service does, what it does not do, guarantees provided

### Meeting Deliverables (produced collectively)

- [ ] **Protocol v1.0 signed off** by all four squads (Catalyst, Hyperion, Nexus, Orion)
- [ ] **Ownership table:** Which squad implements which side of each communication channel
- [ ] **Compatibility criteria:** Breaking vs. non-breaking change definitions agreed upon
- [ ] **Proto Freeze date set:** Date after which breaking changes require explicit versioning and re-negotiation
- [ ] Protocol v1.0 document committed to `/docs/adr/ADR-003-message-protocol.md`
- [ ] Sequence diagram of the protocol committed to `/docs/design/`

---

## 🔒 Proto Freeze Verification

> Required before the **Proto Freeze gate** (End of Week 2).
> This section is completed by the **PL + All squads**.

- [ ] Protocol v1.0 document is finalized and contains: framing, message envelope, all minimum required message types (REGISTER, ACK, ERROR, QUERY_NODE, LIST_NODES, HEARTBEAT), payload encoding, and versioning policy
- [ ] All four squads have explicitly approved the protocol (sign-off recorded in the ADR or meeting notes)
- [ ] Interoperability test plan exists: a client from Squad A can connect to the server of Squad B using this protocol
- [ ] No breaking changes to the protocol are pending
- [ ] ADR-003 is the single authoritative source — no undocumented protocol variants exist in any squad's repository

---

## 🧩 M0 → M1 Transition Readiness

> A squad may only begin M1 implementation tasks after the following are true.
> This is enforced at the Proto Freeze gate.

- [ ] ADR-001 through ADR-006 are all in `Accepted` status and stored in `/docs/adr/`
- [ ] ADR-003 (Protocol v1.0) is signed off by all four squads
- [ ] ADR-004 (Service Boundaries) is complete — the squad's service contract is unambiguous to all other squads
- [ ] The squad's `README.md` references all relevant ADRs with direct links
- [ ] No M0 issues for this squad remain in `Triage`, `Backlog`, or `In Progress` state

---

## ⚠️ M0 Failure Risk Register

> Document any known risks that could block the Proto Freeze gate. Unresolved risks must be
> escalated to the PL before End of Week 1.

| Risk | Impact | Mitigation | Owner | Status |
|------|--------|------------|-------|--------|
| <!-- e.g. Squads cannot agree on payload encoding format --> | <!-- High / Medium / Low --> | <!-- e.g. Schedule alignment meeting by Day 3 of Week 1 --> | <!-- @handle --> | <!-- Open / Resolved --> |

---

*— Exodus Systems Inc. · Engineering Division · EOP Issue Template v1.0 · Binding upon squad onboarding —*
