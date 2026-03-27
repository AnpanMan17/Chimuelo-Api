# Exodus Ops Platform (EOP) — Engineering Project

This project represents the **execution layer** for the development of Exodus Ops Platform (EOP), built by engineering squads within Exodus Systems Inc.

---

## Purpose

This board provides a **centralized view of all engineering work**, enabling:

- Visibility across squads
- Standardized task tracking
- Alignment with product milestones
- Traceability between requirements, code, and decisions

This is not a task list.
It is a **product execution system**.

---

## Working Model

Each squad operates in its own repository and contributes work through GitHub Issues.

All work must be:

- Linked to a clear requirement  
- Properly described with acceptance criteria  
- Assigned and tracked through this board  

This project acts as the **single source of truth for execution tracking**.

---

## Workflow Model

Exodus uses a **controlled execution workflow** defined through the `Workflow Status` field.

All tasks must follow this progression:

```
Triage → Backlog → In Progress → Pending Review → In Review → 'On Hold' → Pending Final Review → In Final Review → Done
```

### Important

- The native GitHub `Status` field is **not used as the authoritative workflow**  
- The `Workflow Status` custom field defines the real execution state
- Any task not following this workflow is considered **invalid and non-evaluable**

---

## Mandatory Fields

Every issue MUST include the following fields:

- **Workflow Status**
- **Team**
- **Milestone**
- **Priority**
- **Size**

Optional but recommended:

- Estimated Days
- Target Date
- Notes

Items with missing mandatory fields will be considered **incomplete** and excluded from evaluation.

---

## Milestones (Product-Oriented)

All work must be aligned to a product milestone:

- **M0 — Product Discovery**
- **M1 — Core Communication Layer**
- **M2 — Processing Capability**
- **M3 — Product API & Integration**
- **M4 — Edge & IoT Integration**

Milestones represent **capability evolution**, not academic phases.

---

## Engineering Principles

All engineering work must adhere to the following principles:

- **Design precedes implementation**
- **Decisions are documented via ADRs**
- **Systems must be observable and testable**
- **Integration is mandatory, not optional**
- **Partial or isolated solutions are not considered complete**

---

## Execution Standards

Adding an issue to this board implies:

- It is part of the **product scope**
- It will be **evaluated under engineering criteria**
- It must comply with defined **contracts and workflows**

This board is used to assess both:

- **Technical delivery**
- **Engineering maturity**

---

## Ownership

Each squad is fully responsible for:

- Task definition
- Architectural decisions
- Implementation quality
- Documentation
- Delivery and integration

There is no shared ownership across squads.
Each team is accountable for its outcomes.
