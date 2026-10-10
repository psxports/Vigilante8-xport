# Vigilante 8

Resolve `[XPORT_ROOT]` from `xport-project.json` and read `[XPORT_ROOT]/AGENTS.md`. Keep only stable game-specific facts and task-routing links here; put detailed evidence under `status`. Never create, edit, move, delete or regenerate `README.md`.

## Project facts

- Native short name: `V8`; language: C
- Solution: `src/platform/win/V8.sln`; Debug executable: `bin/V8_debug.exe`; Release executable: `bin/V8.exe`; working directory: `bin`; intermediates: `_build`
- Runtime data: `bin/DATA`; Red Book output when applicable: `bin/MUSIC`
- Before relying on them, record reviewed image identities, language decision, dummy scope, hooks/layouts, adapter contract and evidence links here

## Reviewed startup evidence

- Boot image: `SLUS_005.10`; immutable input `orig/SLUS_005.10`; SHA-256 `4341e33692ff9a1d20e27c541df0de637463906868a56108a800974ca2a57fcd`; `orig/SYSTEM.CNF` names this executable
- Load: `0x80010000`, payload size `352256`, file offset `2048`; entry `0x800116B4`; runtime GP `0x80065304` from original instructions at `0x800116DC`; header GP is zero
- Implementation language: C, as required by the startup scaffold; this is a port decision rather than a claim about the original source language
- Disc source: configured USA v1.0 CUE; track 01 is data and tracks 02..13 are Red Book audio; hashes are retained in startup inventory
- Accepted exports: `orig/images/SLUS_005.10`; image profile: `tools/ida/SLUS_005.10.json`; reviewed SDK classification: `status/ghidra/classification.json`
- Only executable entrypoint `0x800116B4` is translated during startup; audit: `status/audits/SLUS_005.10-800116B4.md`; no guessed callees or dummy implementations are authorized
- Original startup SP is `0x801FFFF0`; native functions use the host ABI and resolved guest addresses; explicit guest-stack and GP-relative accesses must preserve these original bases
- GPU graph-type guest storage is `0x80064FC4`, bound by the complete getter audit at `0x8004F1E8` in `status/function-coverage/first/coverage-batch-0002-revision-0005.audit.json`
- SDK classification denotes replacement boundaries; wrapper ABI and runtime equivalence remain to be proved during recorded function coverage
- CD callback guest slots: sync `0x8006007C` from original `0x80048FA8`; ready `0x80060080` from original `0x80048FBC`; native bindings in `src/game_batch2.c` and corrections in `status/function-coverage/first/native-delivery.json`. The historical batch-0008 sync label does not describe the ready slot

- Native startup loads the reviewed payload from `bin/BOOT/SLUS_005.10`, mounts the configured CUE and installs its reviewed thirteen-track TOC; evidence: `status/function-coverage/first/native-boot-image-memory.json`, `status/build/native-disc-toc-binding-agent.json`
- Reviewed dynamic module: `Shell/Shell.dll`, SHA-256 `ce77a4cc2b66a6218d032f3b08713e373e7b2f6b4b143df8df616a8667755c48`; entry offset `0xC784`; source identity and relocation evidence: `status/build/shell-first-entry-contract-agent.json`
- Reviewed BIOS backing: `tools/duckstation/data/user/bios/ps-30e.bin`, CEX v3 dated 1995-12-04, SHA-256 `1faaa18fa820a0225e488d9f086296b8e6c46df739666093987ff7d8fd352c09`; native loader validates the whole ROM, retains its storage and copies original ROM `0x10000..0x18BF0` to guest `0x500..0x90F0` before game boot
- Card IRQ initializer is an optional real BIOS backend binding: original `0x63BC` clears `0x75C0`, copies four ordered words `0x6408..0x6418` to `0xCF0..0xD00` and flushes cache at original InitCARD2 callsite `0x5E08`; Shell card patch destinations remain computed from actual kernel words. Evidence: `status/build/native-bios-image-and-init-card-route-agent.json`, `status/build/native-bios-card-irq-binding-applied-root.json`, `status/build/native-real-bios-integration.json`

## Task routing

- Coverage agent coordination: `status/function-coverage/first/agent-workflow.json`; ABI drafts: `status/function-coverage/first/abi-registry.json`

- Current native delivery and runtime blockers: `status/function-coverage/first/native-delivery.json`; historical proof counts are separate from saved native C progress
